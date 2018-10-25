################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/testuser/Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.c 

OBJS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o 

C_DEPS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o: /home/testuser/Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F412Zx -DUSE_HAL_DRIVER -DUSE_STM32412G_DISCOVERY -I"/home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Inc" -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32412G-Discovery -I../../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../../Utilities/Log -I../../../../../../../../Utilities/Fonts -I../../../../../../../../Utilities/CPU  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


