################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/lcd.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/log.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/main.c \
../Example/User/maze.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/mems.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/stm32f4xx_it.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/touchscreen.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/ts_calibration.c 

OBJS += \
./Example/User/lcd.o \
./Example/User/log.o \
./Example/User/main.o \
./Example/User/maze.o \
./Example/User/mems.o \
./Example/User/stm32f4xx_it.o \
./Example/User/touchscreen.o \
./Example/User/ts_calibration.o 

C_DEPS += \
./Example/User/lcd.d \
./Example/User/log.d \
./Example/User/main.d \
./Example/User/maze.d \
./Example/User/mems.d \
./Example/User/stm32f4xx_it.d \
./Example/User/touchscreen.d \
./Example/User/ts_calibration.d 


# Each subdirectory must supply rules for building sources it contributes
Example/User/lcd.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/lcd.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/log.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/log.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/main.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/main.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/%.o Example/User/%.su Example/User/%.cyclo: ../Example/User/%.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/mems.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/mems.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/stm32f4xx_it.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/stm32f4xx_it.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/touchscreen.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/touchscreen.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/ts_calibration.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Projects/STM32F429I-Discovery/Examples/BSP/Src/ts_calibration.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User

clean-Example-2f-User:
	-$(RM) ./Example/User/lcd.cyclo ./Example/User/lcd.d ./Example/User/lcd.o ./Example/User/lcd.su ./Example/User/log.cyclo ./Example/User/log.d ./Example/User/log.o ./Example/User/log.su ./Example/User/main.cyclo ./Example/User/main.d ./Example/User/main.o ./Example/User/main.su ./Example/User/maze.cyclo ./Example/User/maze.d ./Example/User/maze.o ./Example/User/maze.su ./Example/User/mems.cyclo ./Example/User/mems.d ./Example/User/mems.o ./Example/User/mems.su ./Example/User/stm32f4xx_it.cyclo ./Example/User/stm32f4xx_it.d ./Example/User/stm32f4xx_it.o ./Example/User/stm32f4xx_it.su ./Example/User/touchscreen.cyclo ./Example/User/touchscreen.d ./Example/User/touchscreen.o ./Example/User/touchscreen.su ./Example/User/ts_calibration.cyclo ./Example/User/ts_calibration.d ./Example/User/ts_calibration.o ./Example/User/ts_calibration.su

.PHONY: clean-Example-2f-User

