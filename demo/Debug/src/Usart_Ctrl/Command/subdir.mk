################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Usart_Ctrl/Command/Command.c 

OBJS += \
./src/Usart_Ctrl/Command/Command.o 

C_DEPS += \
./src/Usart_Ctrl/Command/Command.d 


# Each subdirectory must supply rules for building sources it contributes
src/Usart_Ctrl/Command/%.o: ../src/Usart_Ctrl/Command/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"D:\ProjetoLPC\Repositorio\EC020\Lib_CMSISv1p30_LPC17xx\inc" -I"D:\ProjetoLPC\Repositorio\EC020\Lib_EaBaseBoard\inc" -I"D:\ProjetoLPC\Repositorio\EC020\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


