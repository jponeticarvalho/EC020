################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portable/Timer/Timer.c 

OBJS += \
./portable/Timer/Timer.o 

C_DEPS += \
./portable/Timer/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
portable/Timer/%.o: ../portable/Timer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -I"D:\ProjetoLPC\Repositorio\EC020\FreeRTOS_Library\include" -I"D:\ProjetoLPC\Repositorio\EC020\Lib_EaBaseBoard\inc" -I"D:\ProjetoLPC\Repositorio\EC020\Lib_MCU\inc" -I"D:\ProjetoLPC\Repositorio\EC020\CMSISv1p30_LPC17xx\inc" -I"D:\ProjetoLPC\Repositorio\EC020\FreeRTOS_Library\portable" -I"D:\ProjetoLPC\Repositorio\EC020\FreeRTOS_Library\demo_code" -O1 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


