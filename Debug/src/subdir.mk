################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/algo_darkspot_correct.cpp \
../src/algo_linear.cpp \
../src/algo_piecewise.cpp \
../src/recolor.cpp 

OBJS += \
./src/algo_darkspot_correct.o \
./src/algo_linear.o \
./src/algo_piecewise.o \
./src/recolor.o 

CPP_DEPS += \
./src/algo_darkspot_correct.d \
./src/algo_linear.d \
./src/algo_piecewise.d \
./src/recolor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Cellar/opencv3/3.2.0/include/ -I/usr/local/Cellar/opencv3/3.2.0/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


