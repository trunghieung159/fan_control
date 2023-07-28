################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Test/test_message_handler.c 

OBJS += \
./Core/Src/Test/test_message_handler.o 

C_DEPS += \
./Core/Src/Test/test_message_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Test/%.o Core/Src/Test/%.su Core/Src/Test/%.cyclo: ../Core/Src/Test/%.c Core/Src/Test/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Test

clean-Core-2f-Src-2f-Test:
	-$(RM) ./Core/Src/Test/test_message_handler.cyclo ./Core/Src/Test/test_message_handler.d ./Core/Src/Test/test_message_handler.o ./Core/Src/Test/test_message_handler.su

.PHONY: clean-Core-2f-Src-2f-Test

