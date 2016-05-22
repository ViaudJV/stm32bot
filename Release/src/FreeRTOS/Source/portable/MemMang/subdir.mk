################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FreeRTOS/Source/portable/MemMang/heap_1.c \
../src/FreeRTOS/Source/portable/MemMang/heap_2.c \
../src/FreeRTOS/Source/portable/MemMang/heap_3.c \
../src/FreeRTOS/Source/portable/MemMang/heap_4.c \
../src/FreeRTOS/Source/portable/MemMang/heap_5.c 

OBJS += \
./src/FreeRTOS/Source/portable/MemMang/heap_1.o \
./src/FreeRTOS/Source/portable/MemMang/heap_2.o \
./src/FreeRTOS/Source/portable/MemMang/heap_3.o \
./src/FreeRTOS/Source/portable/MemMang/heap_4.o \
./src/FreeRTOS/Source/portable/MemMang/heap_5.o 

C_DEPS += \
./src/FreeRTOS/Source/portable/MemMang/heap_1.d \
./src/FreeRTOS/Source/portable/MemMang/heap_2.d \
./src/FreeRTOS/Source/portable/MemMang/heap_3.d \
./src/FreeRTOS/Source/portable/MemMang/heap_4.d \
./src/FreeRTOS/Source/portable/MemMang/heap_5.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/Source/portable/MemMang/%.o: ../src/FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


