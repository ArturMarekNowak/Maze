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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>
#include <stdbool.h>
#include "stm32f4xx_hal_rng.h"
#include "stlogo.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t DemoIndex = 0;
#ifdef EE_M24LR64
uint8_t NbLoop = 1;
#endif /* EE_M24LR64 */
__IO uint8_t ubKeyPressed = RESET; 

BSP_DemoTypedef BSP_examples[]=
{
  {Touchscreen_demo, "TOUCHSCREEN", 0}, 
  {LCD_demo, "LCD", 0}, 
  {Log_demo, "LCD LOG", 0},     
  {MEMS_demo, "MEMS", 0}, 
#ifdef EE_M24LR64
  {EEPROM_demo, "EEPROM", 0}, 
#endif /* EE_M24LR64 */
};

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Display_DemoDescription(void);
bool BallHitTheWall(int array[], int x_position, int y_position, int radius);
bool CalculateIfCollisionOccurred(int array[], int x, int y);

#define  CIRCLE_RADIUS        30

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
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

  uint32_t rnd = 0xff;

  if (HAL_RNG_GenerateRandomNumber(&rng_inst, &rnd) != HAL_OK)
	  return 0xfffffffE;

  start:
  BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER);

  BSP_LCD_SelectLayer(1);

  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  int static maze[255];
  Maze_Generate(maze, 15, 17, &rng_inst);
  Maze_Display(maze, 15, 17, 16, LCD_COLOR_RED);

  int x_position = 22, y_position = 23;
  BSP_LCD_FillCircle(x_position, y_position, 3);

  float Buffer[3];
  float Xval, Yval, Zval = 0x00;
  float sensitivity = 5000.0f;
  int distance = 1;

  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);

  while (1)
  {
	  /* Read Gyro Angular data */
	      BSP_GYRO_GetXYZ(Buffer);

	      /* Update autoreload and capture compare registers value */
	      Xval = Buffer[0];
	      Yval = Buffer[1];
	      Zval = Buffer[2];

	      if (Xval > sensitivity && Yval < sensitivity && Yval > -sensitivity)
	      {
	    	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	    	  BSP_LCD_FillCircle(x_position, y_position, 3);
	    	  y_position += distance;
	    	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	    	  BSP_LCD_FillCircle(x_position, y_position, 3);
	    	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      else if (Xval < -sensitivity && Yval < sensitivity && Yval > -sensitivity)
	      {
	    	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  y_position -= distance;
	      	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      else if (Yval > sensitivity && Xval < sensitivity && Xval > -sensitivity)
	      {
	    	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	    	  BSP_LCD_FillCircle(x_position, y_position, 3);
	    	  x_position += distance;
	    	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	    	  BSP_LCD_FillCircle(x_position, y_position, 3);
	    	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      else if (Yval < -sensitivity && Xval < sensitivity && Xval > -sensitivity)
	      {
	      	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  x_position -= distance;
	      	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      else if (Yval > sensitivity && Xval > sensitivity)
	      {
	      	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  x_position += distance;
	      	  y_position += distance;
	      	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      else if (Yval < -sensitivity && Xval < -sensitivity)
	      {
	      	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  x_position -= distance;
	      	  y_position -= distance;
	      	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      else if (Yval > sensitivity && Xval < -sensitivity)
	      {
	      	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  x_position += distance;
	      	  y_position -= distance;
	      	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      else if (Yval < -sensitivity && Xval > sensitivity)
	      {
	      	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  x_position -= distance;
	      	  y_position += distance;
	      	  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	      	  BSP_LCD_FillCircle(x_position, y_position, 3);
	      	  if (BallHitTheWall(maze, x_position, y_position, 3)) goto start;
	      }
	      HAL_Delay(20);
  }
}

bool BallHitTheWall(int array[], int x_position, int y_position, int radius)
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
			return true;

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
  * @brief  Display main demo messages
  * @param  None
  * @retval None
  */
static void Display_DemoDescription(void)
{
  uint8_t desc[50];
  
  /* Set LCD Foreground Layer  */
  BSP_LCD_SelectLayer(1);
  
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
  
  /* Clear the LCD */ 
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE); 
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);  
  
  /* Display LCD messages */
  BSP_LCD_DisplayStringAt(0, 10, (uint8_t*)"STM32F429I BSP", CENTER_MODE);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(0, 35, (uint8_t*)"Drivers examples", CENTER_MODE);
  
  /* Draw Bitmap */
  BSP_LCD_DrawBitmap((BSP_LCD_GetXSize() - 80)/2, 65, (uint8_t *)stlogo);
  
  BSP_LCD_SetFont(&Font8);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 20, (uint8_t*)"Copyright (c) STMicroelectronics 2017", CENTER_MODE);
  
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, BSP_LCD_GetYSize()/2 + 15, BSP_LCD_GetXSize(), 60);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE); 
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 30, (uint8_t*)"Press USER Button to start:", CENTER_MODE);
  sprintf((char *)desc,"%s example", BSP_examples[DemoIndex].DemoName);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 45, (uint8_t *)desc, CENTER_MODE);   
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

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
 if (GPIO_Pin == KEY_BUTTON_PIN)
 {
   ubKeyPressed = SET;
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
