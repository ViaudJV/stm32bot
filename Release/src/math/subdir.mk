################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/math/Location.cpp \
../src/math/MemsLocation.cpp \
../src/math/Motion.cpp \
../src/math/PID.cpp \
../src/math/VectPlan.cpp \
../src/math/vector2.cpp 

OBJS += \
./src/math/Location.o \
./src/math/MemsLocation.o \
./src/math/Motion.o \
./src/math/PID.o \
./src/math/VectPlan.o \
./src/math/vector2.o 

CPP_DEPS += \
./src/math/Location.d \
./src/math/MemsLocation.d \
./src/math/Motion.d \
./src/math/PID.d \
./src/math/VectPlan.d \
./src/math/vector2.d 


# Each subdirectory must supply rules for building sources it contributes
src/math/%.o: ../src/math/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


