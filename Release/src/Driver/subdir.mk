################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Driver/Buffer.cpp \
../src/Driver/CarteMoteur.cpp \
../src/Driver/Gpio.cpp \
../src/Driver/LIS3DSH.cpp \
../src/Driver/PWM.cpp \
../src/Driver/RollingBuffer.cpp \
../src/Driver/Spi.cpp \
../src/Driver/Uart.cpp \
../src/Driver/Usart.cpp \
../src/Driver/interrupt.cpp \
../src/Driver/timer.cpp 

OBJS += \
./src/Driver/Buffer.o \
./src/Driver/CarteMoteur.o \
./src/Driver/Gpio.o \
./src/Driver/LIS3DSH.o \
./src/Driver/PWM.o \
./src/Driver/RollingBuffer.o \
./src/Driver/Spi.o \
./src/Driver/Uart.o \
./src/Driver/Usart.o \
./src/Driver/interrupt.o \
./src/Driver/timer.o 

CPP_DEPS += \
./src/Driver/Buffer.d \
./src/Driver/CarteMoteur.d \
./src/Driver/Gpio.d \
./src/Driver/LIS3DSH.d \
./src/Driver/PWM.d \
./src/Driver/RollingBuffer.d \
./src/Driver/Spi.d \
./src/Driver/Uart.d \
./src/Driver/Usart.d \
./src/Driver/interrupt.d \
./src/Driver/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Driver/%.o: ../src/Driver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


