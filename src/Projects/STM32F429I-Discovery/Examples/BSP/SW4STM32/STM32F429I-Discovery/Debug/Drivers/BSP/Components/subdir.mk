################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Drivers/BSP/Components/ili9341/ili9341.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Drivers/BSP/Components/l3gd20/l3gd20.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Drivers/BSP/Components/stmpe811/stmpe811.c 

OBJS += \
./Drivers/BSP/Components/ili9341.o \
./Drivers/BSP/Components/l3gd20.o \
./Drivers/BSP/Components/stmpe811.o 

C_DEPS += \
./Drivers/BSP/Components/ili9341.d \
./Drivers/BSP/Components/l3gd20.d \
./Drivers/BSP/Components/stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/ili9341.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Drivers/BSP/Components/ili9341/ili9341.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/l3gd20.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Drivers/BSP/Components/l3gd20/l3gd20.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/stmpe811.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/src/Drivers/BSP/Components/stmpe811/stmpe811.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/STM32F429I-Discovery -I../../../../../../../Utilities/Log -I../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -Wno-unused-variable -Wno-pointer-sign -Wno-main -Wno-format -Wno-address -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-parentheses -Wno-missing-braces -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components

clean-Drivers-2f-BSP-2f-Components:
	-$(RM) ./Drivers/BSP/Components/ili9341.cyclo ./Drivers/BSP/Components/ili9341.d ./Drivers/BSP/Components/ili9341.o ./Drivers/BSP/Components/ili9341.su ./Drivers/BSP/Components/l3gd20.cyclo ./Drivers/BSP/Components/l3gd20.d ./Drivers/BSP/Components/l3gd20.o ./Drivers/BSP/Components/l3gd20.su ./Drivers/BSP/Components/stmpe811.cyclo ./Drivers/BSP/Components/stmpe811.d ./Drivers/BSP/Components/stmpe811.o ./Drivers/BSP/Components/stmpe811.su

.PHONY: clean-Drivers-2f-BSP-2f-Components

