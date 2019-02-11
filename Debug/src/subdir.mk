################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lcd16x2.c \
../src/main.c \
../src/phaseLockedLoop.c \
../src/startup_gcc.c \
../src/systemTimer.c 

OBJS += \
./src/lcd16x2.o \
./src/main.o \
./src/phaseLockedLoop.o \
./src/startup_gcc.o \
./src/systemTimer.o 

C_DEPS += \
./src/lcd16x2.d \
./src/main.d \
./src/phaseLockedLoop.d \
./src/startup_gcc.d \
./src/systemTimer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DPART_TM4C123GH6PM -I"/home/user/workspace/proje/SW-TM4C-2.1.2.111" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


