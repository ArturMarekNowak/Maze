/**
  ******************************************************************************
  * @file    BSP/Src/main.c 
  * @author  MCD Application Team
  * @brief   This example code shows how to use the STM32429I-Discovery BSP Drivers
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "main.h"
#include <math.h>
#include <stdbool.h>
#include "stm32f4xx_hal_rng.h"
#include "stlogo.h"

static void SystemClock_Config(void);
static void Display_DemoDescription(void);
bool BallHitTheLosingWall(int array[], int x_position, int y_position, int radius);
bool BallHitTheWinningWall(int x_position, int y_position);
bool CalculateIfCollisionOccurred(int array[], int x, int y);

int static failures = 0, victories = 0;

int main(void)
{ 
	HAL_Init();

	SystemClock_Config();

	BSP_LCD_Init();
	BSP_GYRO_Init();

	__HAL_RCC_RNG_CLK_ENABLE();
	static RNG_HandleTypeDef rng_inst;

	rng_inst.Instance = RNG;

	if (HAL_RNG_Init(&rng_inst) != HAL_OK)
		return 0xffffffff;

	uint8_t status = 0;
	status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

	start:
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_Clear(LCD_COLOR_LIGHTBLUE);

	char str[100];
	BSP_LCD_DisplayStringAt(5, 280, "failures:", LEFT_MODE);
	sprintf(str, "%d", failures);
	BSP_LCD_DisplayStringAt(85, 280, &str, LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 300, "victories:", LEFT_MODE);
	sprintf(str, "%d", victories);
	BSP_LCD_DisplayStringAt(85, 300, &str, LEFT_MODE);

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(180, 280, 52, 32);
	BSP_LCD_FillRect(120, 280, 52, 32);

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(194, 285, "New", LEFT_MODE);
	BSP_LCD_DisplayStringAt(192, 295, "game", LEFT_MODE);
	BSP_LCD_DisplayStringAt(128, 285, "Reset", LEFT_MODE);
	BSP_LCD_DisplayStringAt(128, 295, "score", LEFT_MODE);
	BSP_LCD_DrawRect(180, 280, 52, 32);
	BSP_LCD_DrawRect(120, 280, 52, 32);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTBLUE);

	int static maze[255];
	Maze_Generate(maze, 15, 17, &rng_inst);
	Maze_Display(maze, 15, 17, 16, LCD_COLOR_DARKBLUE);

	int x_position = 25, y_position = 23;

	BSP_LCD_FillCircle(x_position, y_position, 3);

	float Buffer[3];
	float Xval, Yval, Zval = 0x00;
	float sensitivity = 5000.0f;
	int distance = 1;
	TS_StateTypeDef tsState;

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	while (1)
	{
		BSP_TS_GetState(&tsState);
		if (tsState.TouchDetected == 1)
		{
			if (tsState.X >= 180 && tsState.X <= 180 + 52 &&
				tsState.Y >= 280 && tsState.Y <= 280 + 32)
			{
				goto start;
				HAL_Delay(1500);
			}
			else if (tsState.X >= 120 && tsState.X <= 120 + 52 &&
					 tsState.Y >= 280 && tsState.Y <= 280 + 32)
			{
				victories = 0;
				failures = 0;

				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_DisplayStringAt(5, 280, "failures:", LEFT_MODE);
				sprintf(str, "%d", failures);
				BSP_LCD_DisplayStringAt(85, 280, &str, LEFT_MODE);
				BSP_LCD_DisplayStringAt(5, 300, "victories:", LEFT_MODE);
				sprintf(str, "%d", victories);
				BSP_LCD_DisplayStringAt(85, 300, &str, LEFT_MODE);

				HAL_Delay(50);
			}
		}

		BSP_GYRO_GetXYZ(Buffer);

	    Xval = Buffer[0];
	    Yval = Buffer[1];
	    Zval = Buffer[2];

	    if (Xval > sensitivity && Yval < sensitivity && Yval > -sensitivity)
	    {
	    	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	    	BSP_LCD_FillCircle(x_position, y_position, 3);
	    	y_position += distance;
	    	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	    	BSP_LCD_FillCircle(x_position, y_position, 3);
	    	if (BallHitTheWinningWall(x_position, y_position))
	    	{
	    		DisplayWinningScreen();
	    		goto start;
	    	}
	    	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	    	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    else if (Xval < -sensitivity && Yval < sensitivity && Yval > -sensitivity)
	    {
	    	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	y_position -= distance;
	      	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	if (BallHitTheWinningWall(x_position, y_position))
	        {
	      		DisplayWinningScreen();
	      		goto start;
	      	}
	      	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	      	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    else if (Yval > sensitivity && Xval < sensitivity && Xval > -sensitivity)
	    {
	    	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	    	BSP_LCD_FillCircle(x_position, y_position, 3);
	    	x_position += distance;
	    	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	    	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	if (BallHitTheWinningWall(x_position, y_position))
	        {
	      		DisplayWinningScreen();
	      		goto start;
	      	}
	    	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	    	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    else if (Yval < -sensitivity && Xval < sensitivity && Xval > -sensitivity)
	    {
	      	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	x_position -= distance;
	      	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	if (BallHitTheWinningWall(x_position, y_position))
	        {
	      		DisplayWinningScreen();
	      		goto start;
	      	}
	      	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	      	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    else if (Yval > sensitivity && Xval > sensitivity)
	    {
	      	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	x_position += distance;
	        y_position += distance;
	      	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	if (BallHitTheWinningWall(x_position, y_position))
	        {
	      		DisplayWinningScreen();
	      		goto start;
	      	}
	      	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	      	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    else if (Yval < -sensitivity && Xval < -sensitivity)
	    {
	      	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	x_position -= distance;
	      	y_position -= distance;
	      	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	if (BallHitTheWinningWall(x_position, y_position))
	        {
	      		DisplayWinningScreen();
	      		goto start;
	      	}
	      	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	      	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    else if (Yval > sensitivity && Xval < -sensitivity)
	    {
	      	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	x_position += distance;
	      	y_position -= distance;
	      	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	if (BallHitTheWinningWall(x_position, y_position))
	        {
	      		DisplayWinningScreen();
	      		goto start;
	      	}
	      	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	      	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    else if (Yval < -sensitivity && Xval > sensitivity)
	    {
	      	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	x_position -= distance;
	      	y_position += distance;
	      	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	BSP_LCD_FillCircle(x_position, y_position, 3);
	      	if (BallHitTheWinningWall(x_position, y_position))
	        {
	      		DisplayWinningScreen();
	      		goto start;
	      	}
	      	if (BallHitTheLosingWall(maze, x_position, y_position, 3))
	      	{
	    		DisplayFailureScreen();
	    		goto start;
	    	}
	    }
	    HAL_Delay(20);
	}
}

void DisplayWinningScreen()
{
	BSP_LCD_Clear(LCD_COLOR_LIGHTGREEN);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGREEN);
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(25, 140, "You have won!", LEFT_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTBLUE);
	HAL_Delay(2000);
}

bool BallHitTheWinningWall(int x_position, int y_position)
{
	if (x_position >= 208 && x_position <= 224 && y_position >= 256 && y_position <= 272)
	{
		victories++;
		return true;
	}

	return false;
}

void DisplayFailureScreen()
{
	BSP_LCD_Clear(LCD_COLOR_LIGHTRED);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTRED);
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(25, 140, "You have lost!", LEFT_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTBLUE);
	HAL_Delay(2000);
}

bool BallHitTheLosingWall(int array[], int x_position, int y_position, int radius)
{
	int32_t  d;
	uint32_t  curx;
	uint32_t  cury;

	d = 3 - (radius << 1);
	curx = 0;
	cury = radius;

	while (curx <= cury)
	{
		if (CalculateIfCollisionOccurred(array, x_position + curx, y_position - cury) ||
		CalculateIfCollisionOccurred(array, x_position - curx, y_position - cury) ||
		CalculateIfCollisionOccurred(array, x_position + cury, y_position - curx) ||
		CalculateIfCollisionOccurred(array, x_position - cury, y_position - curx) ||
		CalculateIfCollisionOccurred(array, x_position + curx, y_position + cury) ||
		CalculateIfCollisionOccurred(array, x_position - curx, y_position + cury) ||
		CalculateIfCollisionOccurred(array, x_position + cury, y_position + curx) ||
		CalculateIfCollisionOccurred(array, x_position - cury, y_position + curx))
		{
			failures++;
			return true;
		}

		if (d < 0)
		{
		      d += (curx << 2) + 6;
		}
		else
		{
		      d += ((curx - cury) << 2) + 10;
		      cury--;
		}
		curx++;
	}

	return false;
}

bool CalculateIfCollisionOccurred(int array[], int x, int y)
{
	int row = floor(x / 16);
	int col = floor(y / 16);

	if (!(array[row + 15 * col] == 1)) return false;

	return true;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_RNG_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the Over-Drive mode */
  HAL_PWREx_EnableOverDrive();
    
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

/**
  * @brief  Check for user input
  * @param  None
  * @retval Input state (1 : active / 0 : Inactive)
  */
uint8_t CheckForUserInput(void)
{
  if(BSP_PB_GetState(BUTTON_KEY) == RESET)
  {
    while (BSP_PB_GetState(BUTTON_KEY) == RESET);
    return 1;
  }
  return 0;
}

/**
  * @brief  Toggle LEDs
  * @param  None
  * @retval None
  */
void Toggle_Leds(void)
{
  static uint8_t ticks = 0;
  
  if(ticks++ > 100)
  {
    BSP_LED_Toggle(LED3);
    BSP_LED_Toggle(LED4);
    ticks = 0;
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */
