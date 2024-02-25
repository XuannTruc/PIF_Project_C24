################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DHT11.c \
../Core/Src/FLASH.c \
../Core/Src/ILI9225.c \
../Core/Src/Lunar.c \
../Core/Src/RTC.c \
../Core/Src/clock_func.c \
../Core/Src/main.c \
../Core/Src/rotary_encoder.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/DHT11.o \
./Core/Src/FLASH.o \
./Core/Src/ILI9225.o \
./Core/Src/Lunar.o \
./Core/Src/RTC.o \
./Core/Src/clock_func.o \
./Core/Src/main.o \
./Core/Src/rotary_encoder.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/DHT11.d \
./Core/Src/FLASH.d \
./Core/Src/ILI9225.d \
./Core/Src/Lunar.d \
./Core/Src/RTC.d \
./Core/Src/clock_func.d \
./Core/Src/main.d \
./Core/Src/rotary_encoder.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/DHT11.cyclo ./Core/Src/DHT11.d ./Core/Src/DHT11.o ./Core/Src/DHT11.su ./Core/Src/FLASH.cyclo ./Core/Src/FLASH.d ./Core/Src/FLASH.o ./Core/Src/FLASH.su ./Core/Src/ILI9225.cyclo ./Core/Src/ILI9225.d ./Core/Src/ILI9225.o ./Core/Src/ILI9225.su ./Core/Src/Lunar.cyclo ./Core/Src/Lunar.d ./Core/Src/Lunar.o ./Core/Src/Lunar.su ./Core/Src/RTC.cyclo ./Core/Src/RTC.d ./Core/Src/RTC.o ./Core/Src/RTC.su ./Core/Src/clock_func.cyclo ./Core/Src/clock_func.d ./Core/Src/clock_func.o ./Core/Src/clock_func.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rotary_encoder.cyclo ./Core/Src/rotary_encoder.d ./Core/Src/rotary_encoder.o ./Core/Src/rotary_encoder.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

