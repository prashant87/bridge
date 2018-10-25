################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Src/main.c \
/home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Src/stm32f4xx_hal_msp.c \
/home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Src/stm32f4xx_it.c 

OBJS += \
./Example/User/main.o \
./Example/User/stm32f4xx_hal_msp.o \
./Example/User/stm32f4xx_it.o 

C_DEPS += \
./Example/User/main.d \
./Example/User/stm32f4xx_hal_msp.d \
./Example/User/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Example/User/main.o: /home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F412Zx -DUSE_HAL_DRIVER -DUSE_STM32412G_DISCOVERY -I"/home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Inc" -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32412G-Discovery -I../../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../../Utilities/Log -I../../../../../../../../Utilities/Fonts -I../../../../../../../../Utilities/CPU  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example/User/stm32f4xx_hal_msp.o: /home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F412Zx -DUSE_HAL_DRIVER -DUSE_STM32412G_DISCOVERY -I"/home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Inc" -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32412G-Discovery -I../../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../../Utilities/Log -I../../../../../../../../Utilities/Fonts -I../../../../../../../../Utilities/CPU  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example/User/stm32f4xx_it.o: /home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F412Zx -DUSE_HAL_DRIVER -DUSE_STM32412G_DISCOVERY -I"/home/testuser/projects/bridge.git/cubemx_project/examples/ADC_RegularConversion_Interrupt/Inc" -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32412G-Discovery -I../../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../../Utilities/Log -I../../../../../../../../Utilities/Fonts -I../../../../../../../../Utilities/CPU  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


