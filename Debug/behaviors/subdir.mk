################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../behaviors/Behavior.cpp \
../behaviors/MoveForward.cpp \
../behaviors/TurnInPlace.cpp \
../behaviors/TurnLeft.cpp 

OBJS += \
./behaviors/Behavior.o \
./behaviors/MoveForward.o \
./behaviors/TurnInPlace.o \
./behaviors/TurnLeft.o 

CPP_DEPS += \
./behaviors/Behavior.d \
./behaviors/MoveForward.d \
./behaviors/TurnInPlace.d \
./behaviors/TurnLeft.d 


# Each subdirectory must supply rules for building sources it contributes
behaviors/%.o: ../behaviors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


