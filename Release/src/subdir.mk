################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Buffer.cpp \
../src/Gpio.cpp \
../src/HC-06.cpp \
../src/RollingBuffer.cpp \
../src/Seconde.cpp \
../src/Uart.cpp \
../src/Usart.cpp \
../src/interrupt.cpp \
../src/main.cpp \
../src/timer.cpp 

C_SRCS += \
../src/_initialize_hardware.c \
../src/_write.c 

OBJS += \
./src/Buffer.o \
./src/Gpio.o \
./src/HC-06.o \
./src/RollingBuffer.o \
./src/Seconde.o \
./src/Uart.o \
./src/Usart.o \
./src/_initialize_hardware.o \
./src/_write.o \
./src/interrupt.o \
./src/main.o \
./src/timer.o 

C_DEPS += \
./src/_initialize_hardware.d \
./src/_write.d 

CPP_DEPS += \
./src/Buffer.d \
./src/Gpio.d \
./src/HC-06.d \
./src/RollingBuffer.d \
./src/Seconde.d \
./src/Uart.d \
./src/Usart.d \
./src/interrupt.d \
./src/main.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


