################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f051x8.s 

OBJS += \
./startup/startup_stm32f051x8.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/HAL_Driver/Inc/Legacy" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/Utilities/STM32F0308-Discovery" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/inc" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/CMSIS/device" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/CMSIS/core" -I"/Users/reudy15/Documents/Purdue/ECE_362/STM32F0_KS0108_reudy/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


