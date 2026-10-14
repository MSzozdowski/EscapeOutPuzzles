################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app/app.c \
../Core/Src/app/button.c \
../Core/Src/app/door.c \
../Core/Src/app/lock_input.c 

OBJS += \
./Core/Src/app/app.o \
./Core/Src/app/button.o \
./Core/Src/app/door.o \
./Core/Src/app/lock_input.o 

C_DEPS += \
./Core/Src/app/app.d \
./Core/Src/app/button.d \
./Core/Src/app/door.d \
./Core/Src/app/lock_input.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/app/%.o Core/Src/app/%.su Core/Src/app/%.cyclo: ../Core/Src/app/%.c Core/Src/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Core/Inc/app -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-app

clean-Core-2f-Src-2f-app:
	-$(RM) ./Core/Src/app/app.cyclo ./Core/Src/app/app.d ./Core/Src/app/app.o ./Core/Src/app/app.su ./Core/Src/app/button.cyclo ./Core/Src/app/button.d ./Core/Src/app/button.o ./Core/Src/app/button.su ./Core/Src/app/door.cyclo ./Core/Src/app/door.d ./Core/Src/app/door.o ./Core/Src/app/door.su ./Core/Src/app/lock_input.cyclo ./Core/Src/app/lock_input.d ./Core/Src/app/lock_input.o ./Core/Src/app/lock_input.su

.PHONY: clean-Core-2f-Src-2f-app

