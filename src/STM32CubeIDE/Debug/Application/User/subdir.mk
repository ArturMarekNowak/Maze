################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/Maze/Src/main.c \
../Application/User/stm32f429i_discovery.c \
../Application/User/stm32f429i_discovery_eeprom.c \
../Application/User/stm32f429i_discovery_gyroscope.c \
../Application/User/stm32f429i_discovery_io.c \
../Application/User/stm32f429i_discovery_lcd.c \
../Application/User/stm32f429i_discovery_sdram.c \
../Application/User/stm32f429i_discovery_ts.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/Maze/Src/stm32f4xx_hal_msp.c \
C:/Users/artur/OneDrive/Desktop/Workspace/Maze/Maze/Src/stm32f4xx_it.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c 

OBJS += \
./Application/User/main.o \
./Application/User/stm32f429i_discovery.o \
./Application/User/stm32f429i_discovery_eeprom.o \
./Application/User/stm32f429i_discovery_gyroscope.o \
./Application/User/stm32f429i_discovery_io.o \
./Application/User/stm32f429i_discovery_lcd.o \
./Application/User/stm32f429i_discovery_sdram.o \
./Application/User/stm32f429i_discovery_ts.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_it.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o 

C_DEPS += \
./Application/User/main.d \
./Application/User/stm32f429i_discovery.d \
./Application/User/stm32f429i_discovery_eeprom.d \
./Application/User/stm32f429i_discovery_gyroscope.d \
./Application/User/stm32f429i_discovery_io.d \
./Application/User/stm32f429i_discovery_lcd.d \
./Application/User/stm32f429i_discovery_sdram.d \
./Application/User/stm32f429i_discovery_ts.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_it.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/main.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/Maze/Src/main.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/%.o Application/User/%.su Application/User/%.cyclo: ../Application/User/%.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32f4xx_hal_msp.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/Maze/Src/stm32f4xx_hal_msp.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32f4xx_it.o: C:/Users/artur/OneDrive/Desktop/Workspace/Maze/Maze/Src/stm32f4xx_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User

clean-Application-2f-User:
	-$(RM) ./Application/User/main.cyclo ./Application/User/main.d ./Application/User/main.o ./Application/User/main.su ./Application/User/stm32f429i_discovery.cyclo ./Application/User/stm32f429i_discovery.d ./Application/User/stm32f429i_discovery.o ./Application/User/stm32f429i_discovery.su ./Application/User/stm32f429i_discovery_eeprom.cyclo ./Application/User/stm32f429i_discovery_eeprom.d ./Application/User/stm32f429i_discovery_eeprom.o ./Application/User/stm32f429i_discovery_eeprom.su ./Application/User/stm32f429i_discovery_gyroscope.cyclo ./Application/User/stm32f429i_discovery_gyroscope.d ./Application/User/stm32f429i_discovery_gyroscope.o ./Application/User/stm32f429i_discovery_gyroscope.su ./Application/User/stm32f429i_discovery_io.cyclo ./Application/User/stm32f429i_discovery_io.d ./Application/User/stm32f429i_discovery_io.o ./Application/User/stm32f429i_discovery_io.su ./Application/User/stm32f429i_discovery_lcd.cyclo ./Application/User/stm32f429i_discovery_lcd.d ./Application/User/stm32f429i_discovery_lcd.o ./Application/User/stm32f429i_discovery_lcd.su ./Application/User/stm32f429i_discovery_sdram.cyclo ./Application/User/stm32f429i_discovery_sdram.d ./Application/User/stm32f429i_discovery_sdram.o ./Application/User/stm32f429i_discovery_sdram.su ./Application/User/stm32f429i_discovery_ts.cyclo ./Application/User/stm32f429i_discovery_ts.d ./Application/User/stm32f429i_discovery_ts.o ./Application/User/stm32f429i_discovery_ts.su ./Application/User/stm32f4xx_hal_msp.cyclo ./Application/User/stm32f4xx_hal_msp.d ./Application/User/stm32f4xx_hal_msp.o ./Application/User/stm32f4xx_hal_msp.su ./Application/User/stm32f4xx_it.cyclo ./Application/User/stm32f4xx_it.d ./Application/User/stm32f4xx_it.o ./Application/User/stm32f4xx_it.su ./Application/User/syscalls.cyclo ./Application/User/syscalls.d ./Application/User/syscalls.o ./Application/User/syscalls.su ./Application/User/sysmem.cyclo ./Application/User/sysmem.d ./Application/User/sysmem.o ./Application/User/sysmem.su

.PHONY: clean-Application-2f-User
