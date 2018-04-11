################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Display_Ctrl/Oled_Ctrl/Fonte5x7.c \
../src/Display_Ctrl/Oled_Ctrl/Oled_Ctrl.c 

OBJS += \
./src/Display_Ctrl/Oled_Ctrl/Fonte5x7.o \
./src/Display_Ctrl/Oled_Ctrl/Oled_Ctrl.o 

C_DEPS += \
./src/Display_Ctrl/Oled_Ctrl/Fonte5x7.d \
./src/Display_Ctrl/Oled_Ctrl/Oled_Ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
src/Display_Ctrl/Oled_Ctrl/%.o: ../src/Display_Ctrl/Oled_Ctrl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"D:\Topicos Avancados\Lib_CMSISv1p30_LPC17xx\inc" -I"D:\Topicos Avancados\Lib_EaBaseBoard\inc" -I"D:\Topicos Avancados\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


