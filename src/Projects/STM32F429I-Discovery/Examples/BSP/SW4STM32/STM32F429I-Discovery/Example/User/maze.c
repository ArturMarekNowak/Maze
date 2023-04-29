/*
 * maze_algorithm.c
 *
 *  Created on: 23 kwi 2023
 *      Author: artur
 */

#include "main.h"
#include "maze.h"
#include "stm32f429i_discovery_lcd.h"
#include <time.h>
#include <stdlib.h>
#include "stdint.h"

void Maze_Display(const int maze[], const int width, const int height, const int rectangle_side_size, uint32_t color) {

	int i, j, top_left_rectangle_pixel_X = 0, top_left_rectangle_pixel_Y = 0;

	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			int debug = maze[j * width + i];
			if(debug == 1)
			{
				LCD_Drawing_Rectangle(top_left_rectangle_pixel_X, top_left_rectangle_pixel_Y, rectangle_side_size, rectangle_side_size, color);
			}

			top_left_rectangle_pixel_X += rectangle_side_size;
      }

	  top_left_rectangle_pixel_X = 0;
	  top_left_rectangle_pixel_Y += rectangle_side_size;
   }
}

void Maze_Generate(int array[], const int width, const int height, RNG_HandleTypeDef *hrng) {

   int x, y;
   /* Initialize the maze. */
   for(x = 0; x < width * height; x++) {

	   array[x] = 1;
   }

   /* Carve the maze. */
   for(y = 1; y < height; y += 2) {
      for(x = 1; x < width; x += 2) {
    	  Maze_Carve(array, width, height, x, y, hrng);
      }
   }

   /* Set up an entry and an exit. */
   array[16] = 0; //Maze entry
   array[(height - 1) * width + (width - 2)] = 0;
}

void Maze_Carve(int maze[], const int width, const int height, int x, int y, RNG_HandleTypeDef *hrng) {

   int x1, y1;
   int x2, y2;
   int dx, dy;
   int dir, count;
   uint32_t generatedNumber;

   HAL_RNG_GenerateRandomNumber(hrng, &generatedNumber);

   dir = generatedNumber % 4;

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
         HAL_RNG_GenerateRandomNumber(hrng, &generatedNumber);
         dir = generatedNumber % 4;
         count = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
      }
   }

}
