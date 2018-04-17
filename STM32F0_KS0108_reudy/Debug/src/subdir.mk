################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/KS0108-STM32.c \
../src/KS0108.c \
../src/graphic.c \
../src/main.c \
../src/stm32f0xx_it.c \
../src/syscalls.c \
../src/system_stm32f0xx.c 

OBJS += \
./src/KS0108-STM32.o \
./src/KS0108.o \
./src/graphic.o \
./src/main.o \
./src/stm32f0xx_it.o \
./src/syscalls.o \
./src/system_stm32f0xx.o 

C_DEPS += \
./src/KS0108-STM32.d \
./src/KS0108.d \
./src/graphic.d \
./src/main.d \
./src/stm32f0xx_it.d \
./src/syscalls.d \
./src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F051R8Tx -DSTM32F0DISCOVERY -DDEBUG -DSTM32F051x8 -DUSE_HAL_DRIVER -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/HAL_Driver/Inc/Legacy" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/Utilities/STM32F0308-Discovery" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/inc" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/CMSIS/device" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/CMSIS/core" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


