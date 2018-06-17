################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Usart_Ctrl/Command/subdir.mk
-include src/Usart_Ctrl/subdir.mk
-include src/EasyWeb_Ctrl/subdir.mk
-include src/Display_Ctrl/Temp_Ctrl/subdir.mk
-include src/Display_Ctrl/Ssp_Ctrl/subdir.mk
-include src/Display_Ctrl/Oled_Ctrl/subdir.mk
-include src/Display_Ctrl/Light_Ctrl/subdir.mk
-include src/Display_Ctrl/I2c_Ctrl/subdir.mk
-include src/Display_Ctrl/Button_Ctrl/subdir.mk
-include src/Display_Ctrl/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: demo.axf

# Tool invocations
demo.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\ProjetoLPC\Repositorio\EC020\Lib_CMSISv1p30_LPC17xx\Debug" -L"D:\ProjetoLPC\Repositorio\EC020\FreeRTOS_Library\Debug" -L"D:\ProjetoLPC\Repositorio\EC020\Lib_EaBaseBoard\Debug" -L"D:\ProjetoLPC\Repositorio\EC020\Lib_MCU\Debug" -Xlinker --gc-sections -Xlinker -Map=demo.map -mcpu=cortex-m3 -mthumb -T "demo_Debug.ld" -o "demo.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) demo.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size demo.axf; # arm-none-eabi-objdump -h -S demo.axf >demo.lss
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
