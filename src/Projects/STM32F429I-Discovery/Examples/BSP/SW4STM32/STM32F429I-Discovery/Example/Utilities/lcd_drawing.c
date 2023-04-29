/*
 * lcd_drawing.c
 *
 *  Created on: 23 kwi 2023
 *      Author: artur
 */

#include "stm32f429i_discovery_lcd.h"
#include "lcd_drawing.h"

void LCD_Drawing_Rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color)
{
	BSP_LCD_SetTextColor(color);
	BSP_LCD_FillRect(x, y, width, height);
}
