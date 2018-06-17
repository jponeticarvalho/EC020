################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Display_Ctrl/Light_Ctrl/Light_Ctrl.c 

OBJS += \
./src/Display_Ctrl/Light_Ctrl/Light_Ctrl.o 

C_DEPS += \
./src/Display_Ctrl/Light_Ctrl/Light_Ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
src/Display_Ctrl/Light_Ctrl/%.o: ../src/Display_Ctrl/Light_Ctrl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"D:\ProjetoLPC\Repositorio\EC020\Lib_CMSISv1p30_LPC17xx\inc" -I"D:\ProjetoLPC\Repositorio\EC020\FreeRTOS_Library\portable" -I"D:\ProjetoLPC\Repositorio\EC020\FreeRTOS_Library\include" -I"D:\ProjetoLPC\Repositorio\EC020\FreeRTOS_Library\demo_code" -I"D:\ProjetoLPC\Repositorio\EC020\Lib_EaBaseBoard\inc" -I"D:\ProjetoLPC\Repositorio\EC020\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


