################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Robot/HC-06.cpp \
../src/Robot/L298PTwinV11.cpp \
../src/Robot/Robot.cpp \
../src/Robot/TB6612FNG.cpp 

OBJS += \
./src/Robot/HC-06.o \
./src/Robot/L298PTwinV11.o \
./src/Robot/Robot.o \
./src/Robot/TB6612FNG.o 

CPP_DEPS += \
./src/Robot/HC-06.d \
./src/Robot/L298PTwinV11.d \
./src/Robot/Robot.d \
./src/Robot/TB6612FNG.d 


# Each subdirectory must supply rules for building sources it contributes
src/Robot/%.o: ../src/Robot/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


