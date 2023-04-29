################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Example/Utilities/lcd_drawing.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Utilities/Log/lcd_log.c 

OBJS += \
./Example/Utilities/lcd_drawing.o \
./Example/Utilities/lcd_log.o 

C_DEPS += \
./Example/Utilities/lcd_drawing.d \
./Example/Utilities/lcd_log.d 


# Each subdirectory must supply rules for building sources it contributes
Example/Utilities/%.o Example/Utilities/%.su Example/Utilities/%.cyclo: ../Example/Utilities/%.c Example/Utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/Utilities/lcd_log.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Utilities/Log/lcd_log.c Example/Utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-Utilities

clean-Example-2f-Utilities:
	-$(RM) ./Example/Utilities/lcd_drawing.cyclo ./Example/Utilities/lcd_drawing.d ./Example/Utilities/lcd_drawing.o ./Example/Utilities/lcd_drawing.su ./Example/Utilities/lcd_log.cyclo ./Example/Utilities/lcd_log.d ./Example/Utilities/lcd_log.o ./Example/Utilities/lcd_log.su

.PHONY: clean-Example-2f-Utilities

