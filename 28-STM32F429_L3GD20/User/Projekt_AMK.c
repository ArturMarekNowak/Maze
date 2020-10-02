/** Credits 
 *	Libraries for this project are provided by Tilen MAJERLE, Maze Algorithm Generation by Joe Wingbermuehle and heapsort by Geeks for Geeks site
 * 
 *	Based on Keil project for L3GD20 3x Gryo on STM32F429 Discovery board
 *
 *	Designed for STM32F429-Discovery board
 *
 *	@author		Tilen MAJERLE
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.net
 *	@ide		Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 *
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen MAJERLE, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 *
 * |---------------------------------------------------------------------- 
 * | Copyright (c) 2015, Joe Wingbermuehle
 * | All rights reserved.
 * | 
 * | Redistribution and use in source and binary forms, with or without
 * | modification, are permitted provided that the following conditions are met:
 * |     * Redistributions of source code must retain the above copyright
 * |       notice, this list of conditions and the following disclaimer.
 * |     * Redistributions in binary form must reproduce the above copyright
 * |       notice, this list of conditions and the following disclaimer in the
 * |       documentation and/or other materials provided with the distribution.
 * |     * Neither the name of the <organization> nor the
 * |       names of its contributors may be used to endorse or promote products
 * |       derived from this software without specific prior written permission.
 * | 
 * | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * | ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * | WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * | DISCLAIMED. IN NO EVENT SHALL Joe Wingbermuehle BE LIABLE FOR ANY
 * | DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * | (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * | LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * | ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * | SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * |  
 * |---------------------------------------------------------------------- 
 */
 
 
#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_l3gd20.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_ili9341_ltdc.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_rng.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32f4_spi_dma.h"
#include "tm_stm32f4_dma.h"
#include "tm_stm32f4_i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*Macros*/
#define distance 1
#define time_of_delay 20

/*Labirynth*/
void DrawLabirynthStatic(void);
void GenerateMaze(int [],const int,const int );
void ShowMaze(const int[],const int,const int);
void CarveMaze(int[],const int,const int, int, int);

/*Collision Detetcion*/
int CollisionDetection(int,int,int[],int);
int binarySearch(int[], int, int, int); 
void heapify(int[], int, int);
void heapSort(int[], int);

/*Screens*/
void VictoryScreen(int,int);
void FailureScreen(int,int);


int main(void) {
	
	/* Initialization of variables with position of ball, loop iterator, number of walls counter, variable needed for conversion of point (X,Y) to Z, victories and failures counter */
	int x_position = 23, y_position = 23, iterator = 0, conversion = 0, victories = 0, failures = 0; 
	
	/* Rows and columns of maze are stored in maze[] array, each wall is equal to 1, each path block is equal to 0 */
	int static maze[255];
	
	/* Width and Length of maze and radius of ball */
	const int width = 15, length = 17, radius = 2;
	
	/* Buffer for strings display */
	char buffer[20];
	
	/* Variables needed for circle creation */
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int xxx = 0;
	int yyy = radius;
	
	/* Create TouchData struct */
	TM_STMPE811_TouchData touchData;
	
	/* L3GD20 Struct */
	TM_L3GD20_t L3GD20_Data;
	
	/* Initialize system */
	SystemInit();
	
	/* Initialize button on board */
	TM_DISCO_ButtonInit();
	
	/* Initialize delay */
	TM_DELAY_Init();
	
	/*Initialize RNG*/
	TM_RNG_Init();
	
	/* Initialize leds on board */
	TM_DISCO_LedInit();
	
	/* Init ILI9341 with LTDC on STM32F429 Discovery board */
	TM_ILI9341_Init();
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
	
	/* Select touch screen orientation */
	touchData.orientation = TM_STMPE811_Orientation_Portrait_2;
	
	/* Initialize Touch */
	if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
		TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
		
		while (1);
	}
	
	/* Init L3GD20 sensor */
	if (TM_L3GD20_Init(TM_L3GD20_Scale_2000) != TM_L3GD20_Result_Ok) {
		/* Sensor error */
		TM_ILI9341_Puts(10, 100, "Sensor ERROR!", &TM_Font_11x18, 0x0000, ILI9341_COLOR_BLUE2);
		
		while (1);
	}

	/* Exit from nested loop - beginning of new game, initialization of ball starting points */
	start:
	x_position = 23;
	y_position = 23;
	
	/* Fill of background */
	TM_ILI9341_Fill(ILI9341_COLOR_BLUE2);
	
	/* Maze generation - at this point we are generating maze in maze array where each 1 corresponds to 16 pix * 16 pix square wall 
	and zero corresponds to 16 pix * 16 pix square space */
	GenerateMaze(maze,width,length);

	/* Initialization of array with wall ID number - in this array each wall equal to 1 in maze array will have its sides unique ID number */
	static int array_of_walls_ID_numbers[8700];
	
	/* Initialization of additional iterators, pixels coordinats which will be stored in the array and counter of pixels added to array 
	counter variable is for debugging purposes only */
	int iterator_1, iterator_2, x_pixel = 0, y_pixel = 0, counter = 0;

	/* This part of the code is responsible for assigning to each pixel creating side of the wall a unique ID */
  for(iterator_2 = 0; iterator_2 < length; iterator_2++)//Next row 
	{
    for(iterator_1 = 0; iterator_1 < width; iterator_1++) //Next coulmn
		{
			if(maze[iterator_2 * width + iterator_1] == 1)  //If maze[] == 1 then there is a wall here
			{				
				for(iterator = 0; iterator < 16; iterator++) //Pixels of top of the square
				{
					conversion = 0.5*(x_pixel+y_pixel)*(x_pixel+y_pixel+1)+y_pixel; //Converting pixels coordinates using pairing function
					array_of_walls_ID_numbers[counter] = conversion; //Placing an ID number of pixel in an array
					counter++; //Number of pixels stored incrementation
					x_pixel++; //Next pixel to right
				}
				x_pixel--;
						
				for(iterator = 0; iterator < 15; iterator++) //Pixels of right side of the square
				{
					conversion = 0.5*(x_pixel+y_pixel)*(x_pixel+y_pixel+1)+y_pixel;
					array_of_walls_ID_numbers[counter] = conversion;
					counter++;
					y_pixel++;	
				}
						
				for(iterator = 0; iterator < 15; iterator++) //Pixels of bottom of the square
				{
					conversion = 0.5*(x_pixel+y_pixel)*(x_pixel+y_pixel+1)+y_pixel;
					array_of_walls_ID_numbers[counter] = conversion;
					counter++;
					x_pixel--;
				}
										
				for(iterator = 0; iterator < 15; iterator++) //Pixels of left side of the square
				{
					conversion = 0.5*(x_pixel+y_pixel)*(x_pixel+y_pixel+1)+y_pixel;
					array_of_walls_ID_numbers[counter] = conversion;
					counter++;
					y_pixel--;
				}
			}
			
			x_pixel += 16; //Next square to the right
			
    }
		
		x_pixel = 0;    //Coming back to the beginning of the row
		y_pixel += 16;  //Next row
		
  }

	int n = sizeof(array_of_walls_ID_numbers)/sizeof(array_of_walls_ID_numbers[0]);

	/* Heap sort of array of walls ID numbers required for binary search */
	heapSort(array_of_walls_ID_numbers,n);

	while (1) 
	{
		/* Read data from gyroscope */
		TM_L3GD20_Read(&L3GD20_Data);
		
		/* If user button pressed */
		if(TM_DISCO_ButtonPressed())
		{	
			/* Fill background */
			TM_ILI9341_Fill(ILI9341_COLOR_BLUE2);
			while(1)
			{
				/* Read data from gyroscope */
				TM_L3GD20_Read(&L3GD20_Data);
					
				/* Information */
				TM_ILI9341_Puts(10, 10, "L3GD20 3-Axis\nGyroscope", &TM_Font_11x18, 0x0000, ILI9341_COLOR_BLUE2);

				/* Display data on LCD */
				sprintf(buffer, "X rotation: %4d", L3GD20_Data.X);
				TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_BLUE2);
				sprintf(buffer, "Y rotation: %4d", L3GD20_Data.Y);
				TM_ILI9341_Puts(10, 122, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_BLUE2);
				sprintf(buffer, "Z rotation: %4d", L3GD20_Data.Z);
				TM_ILI9341_Puts(10, 144, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_BLUE2);
					
				/* Display current number of victories and failures */
				sprintf(buffer, "Victories: %4d", victories);
				TM_ILI9341_Puts(10, 188, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_BLUE2);
				sprintf(buffer, " Failures: %4d", failures);
				TM_ILI9341_Puts(10, 210, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_BLUE2);
					
				if(TM_DISCO_ButtonPressed())
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			/* Fill background */
			TM_ILI9341_Fill(ILI9341_COLOR_BLUE2);
			
			/* Show maze */
			ShowMaze(maze,width,length);
				
			/* Draw "buttons" on touch panel */
			TM_ILI9341_DrawRoundedRectangle(5, 277, 70, 315, 2, ILI9341_COLOR_BLACK);
			TM_ILI9341_DrawFilledRectangle(6, 278, 69, 314, ILI9341_COLOR_WHITE);
			TM_ILI9341_DrawRoundedRectangle(170, 277, 235, 315, 2, ILI9341_COLOR_BLACK);
			TM_ILI9341_DrawFilledRectangle(171, 278, 234, 314, ILI9341_COLOR_WHITE);
			
			/* Name "buttons" */
			sprintf(buffer, "Reset\nScore");
			TM_ILI9341_Puts(20, 286, buffer, &TM_Font_7x10, 0x0000, ILI9341_COLOR_WHITE);
			sprintf(buffer, "New Map");
			TM_ILI9341_Puts(178, 290, buffer, &TM_Font_7x10, 0x0000, ILI9341_COLOR_WHITE);
			
			/* Display current number of victories and failures */
			sprintf(buffer, "Victories:%d", victories);
			TM_ILI9341_Puts(80, 285, buffer, &TM_Font_7x10, 0x0000, ILI9341_COLOR_BLUE2);
			sprintf(buffer, "Failures:%d", failures);
			TM_ILI9341_Puts(80, 300, buffer, &TM_Font_7x10, 0x0000, ILI9341_COLOR_BLUE2);
			
			while(1)
			{
				/* Read data from gyroscope */
				TM_L3GD20_Read(&L3GD20_Data);
		
				/* If touch was detected on touch panel */
				if (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) 
				{
					/* If first "button" was pressed */
					if((touchData.x > 5 && touchData.x < 70) && (touchData.y > 277 && touchData.y < 315))
					{
						/* Reset score */
						victories = 0;
						failures =0;
										
						sprintf(buffer, "Victories:%d", victories);
						TM_ILI9341_Puts(80, 285, buffer, &TM_Font_7x10, 0x0000, ILI9341_COLOR_BLUE2);
						sprintf(buffer, "Failures:%d", failures);
						TM_ILI9341_Puts(80, 300, buffer, &TM_Font_7x10, 0x0000, ILI9341_COLOR_BLUE2);
										
						Delayms(50);
					}
								
					/* If second "button" was pressed */
					if((touchData.x > 170 && touchData.x < 235) && (touchData.y > 277 && touchData.y < 315))
					{
						/* New game */
						Delayms(50);
						goto start;
					}	
						
				}
						
				/* Create ball */
				TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
				
				f = 1 - radius;
				ddF_x = 1;
				ddF_y = -2 * radius;
				xxx = 0;
				yyy = radius;

				while (xxx < yyy) 
				{
					if (f >= 0) 
					{
						yyy--;
						ddF_y += 2;
						f += ddF_y;
					}
					xxx++;
					ddF_x += 2;
					f += ddF_x;
					
						
					/* If gyroscope detects change of orientation */ 
					if(L3GD20_Data.X>10 && L3GD20_Data.Y<10 && L3GD20_Data.Y>-10)
					{
							
						/* Draw ball in new position and fill the position the ball has left */
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						y_position += distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);

						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
								
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						} 
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
								
							/* Increase win counter and display win screen for 2 sec */
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
							
					}
						
						
					/* If gyroscope detects change of orientation */ 
					if(L3GD20_Data.X<-10 && L3GD20_Data.Y<10 && L3GD20_Data.Y>-10)
					{
						/* Draw ball in new position and fill the position the ball has left */
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						y_position -= distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);
							
						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
								||CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
							
					}
						
					/* If gyroscope detects change of orientation */ 
					if(L3GD20_Data.Y>10 && L3GD20_Data.X<10 && L3GD20_Data.X>-10)
					{
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						x_position += distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);
							
						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
					}
						
					/* If gyroscope detects change of orientation */ 
					if(L3GD20_Data.Y<-10 && L3GD20_Data.X<10 && L3GD20_Data.X>-10)
					{
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						x_position -= distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);
						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
					}
						
					/* If gyroscope detects change of orientation */						
					if(L3GD20_Data.Y>10 && L3GD20_Data.X>10)
					{
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						x_position += distance;
						y_position += distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);
						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
									|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
					}
						
						
					/* If gyroscope detects change of orientation */						
					if(L3GD20_Data.Y<-10 && L3GD20_Data.X<-10)
					{
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						x_position -= distance;
						y_position -= distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);
						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
							|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
					}
						
						
					/* If gyroscope detects change of orientation */						
					if(L3GD20_Data.Y<-10 && L3GD20_Data.X>10)
					{
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						x_position -= distance;
						y_position += distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);
						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
					}
						
					/* If gyroscope detects change of orientation */
					if(L3GD20_Data.Y>10 && L3GD20_Data.X<-10)
					{
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE2);
						x_position += distance;
						y_position -= distance;
						TM_ILI9341_DrawFilledCircle(x_position,y_position,radius,ILI9341_COLOR_BLUE);
						Delayms(time_of_delay);
						/* If ID number of new coordinate of edge of the ball is detected in array of walls ID number */
						if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) > -1 
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) > -1)
						{
							/* Increase failure counter and display fail screen for 2 sec */
							failures += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_RED);
							sprintf(buffer, " Failure!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_RED);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						/* Else if ball reaches the exit end the game with win */
						else if(CollisionDetection(x_position,y_position+radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position,y_position-radius,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-radius,y_position,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position+yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-xxx,y_position-yyy,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position+yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position+xxx,array_of_walls_ID_numbers,n) == -5
								|| CollisionDetection(x_position-yyy,y_position-xxx,array_of_walls_ID_numbers,n) == -5)
						{
							victories += 1;
							TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
							sprintf(buffer, " Victory!!!\nTotal victories: %d\nTotal failures: %d",victories, failures);
							TM_ILI9341_Puts(10, 100, buffer, &TM_Font_11x18, 0x0000, ILI9341_COLOR_GREEN);
							Delayms(2000);
							goto start; //Leave nested loop and start new game
						}
						else
						{
							continue;
						}
					}
				}
						
				if(TM_DISCO_ButtonPressed())
				{	
					break;
				}
					
			}
		}
	}
}


////////////////////////////////////////COLLISION DETECTION////////////////////////////////////////////////////////


void heapify(int arr[], int n, int i) 
{ 
	int temp;
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        //swap(arr[i], arr[largest]); 
  		temp = arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;
  		
  		
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
} 
  
// main function to do heap sort 
void heapSort(int arr[], int n) 
{ 
	int i, temp;
    // Build heap (rearrange array) 
    for (i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        //swap(arr[0], arr[i]); 
        temp = arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
    } 
} 

int binarySearch(int arr[], int smallest, int biggest, int my_precious) 
{ 
    if (biggest >= smallest) { 
        int center = smallest + (biggest - smallest) / 2; 

        if (arr[center] == my_precious) 
            return center; 

        if (arr[center] > my_precious) 
            return binarySearch(arr, smallest, center - 1, my_precious); 
				
        return binarySearch(arr, center + 1, biggest, my_precious); 
    } 
    return -1; 
} 


int CollisionDetection(int x_pixel, int y_pixel,int array_of_walls_ID_numbers[],int n)
{
	/* If pixel is in the within winning borders */
	if((x_pixel > 207 && x_pixel < 224) && y_pixel > 256) 
	{	
		return -5;
	}
	else 
	{
		/* If pixel is  not in the within winning borders calculate its ID and find them in ID array */
		float my_precious = (0.5*(x_pixel+y_pixel)*(x_pixel+y_pixel+1)+y_pixel);
		if(binarySearch(array_of_walls_ID_numbers, 0, n-1, my_precious) == -1)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}



////////////////////////////////////////MAZE ALGORITHM////////////////////////////////////////////////////////

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(int maze[],const int width,const int height) {

   int x, y;
   /* Initialize the maze. */
   for(x = 0; x < width * height; x++) {

      maze[x] = 1;
   }
	
   /* Carve the maze. */
   for(y = 1; y < height; y += 2) {
      for(x = 1; x < width; x += 2) {
         CarveMaze(maze, width, height, x, y);
      }
   }
	 
   /* Set up an entry and an exit. */
	 maze[16] = 0; //Maze entry
   maze[(height - 1) * width + (width - 2)] = 0;
}

/* Display the maze. */
void ShowMaze(const int maze[],const int width,const int height) {

   int x, y, TL_x_pixel = 0, TL_y_pixel = 0, BR_x_pixel = 15, BR_y_pixel = 15;
	
	
	
   for(y = 0; y < height; y++) 
	{
      for(x = 0; x < width; x++) 
		  {
				 if(maze[y * width + x] == 1)
				 {
					  TM_ILI9341_DrawFilledRectangle(TL_x_pixel,TL_y_pixel,BR_x_pixel,BR_y_pixel,ILI9341_COLOR_BLUE);
				 }
				 else
				 {
					  TM_ILI9341_DrawFilledRectangle(TL_x_pixel,TL_y_pixel,BR_x_pixel,BR_y_pixel,ILI9341_COLOR_BLUE2); 
				 }
				 
				 TL_x_pixel += 16;
				 BR_x_pixel += 16;
      }
      TL_x_pixel = 0;
			BR_x_pixel = 15;
			TL_y_pixel += 16;
			BR_y_pixel += 16;
   }
		 TM_ILI9341_DrawFilledRectangle(208, 256, 223, 271, ILI9341_COLOR_ORANGE);

}

/*  Carve the maze starting at x, y. */
void CarveMaze(int maze[],const int width,const int height, int x, int y) {

   int x1, y1;
   int x2, y2;
   int dx, dy;
   int dir, count;

	dir = TM_RNG_Get() % 4;
	
   count = 0;
   while(count < 4) {
      dx = 0; dy = 0;
      switch(dir) {
      case 0:  dx = 1;  break;
      case 1:  dy = 1;  break;
      case 2:  dx = -1; break;
      default: dy = -1; break;
      }
      x1 = x + dx;
      y1 = y + dy;
      x2 = x1 + dx;
      y2 = y1 + dy;
      if(   x2 > 0 && x2 < width && y2 > 0 && y2 < height
         && maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
         maze[y1 * width + x1] = 0;
         maze[y2 * width + x2] = 0;
         x = x2; y = y2;
         dir = TM_RNG_Get() % 4;
         count = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
      }
   }

}
