/*
 * maze_algorithm.h
 *
 *  Created on: 23 kwi 2023
 *      Author: artur
 */

#ifndef EXAMPLE_USER_MAZE_H_
#define EXAMPLE_USER_MAZE_H_

#include "stdint.h"
#include "stm32f4xx_hal_rng.h"
#include "../Utilities/lcd_drawing.h"

void Maze_Generate(int maze[], const int width,const int height, RNG_HandleTypeDef *hrng);
void Maze_Carve(int maze[],const int width,const int height, int x, int y, RNG_HandleTypeDef *hrng);
void Maze_Display(const int maze[], const int width, const int height, const int rectangle_side_size, uint32_t color);

#endif /* EXAMPLE_USER_MAZE_H_ */
