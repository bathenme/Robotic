################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../behaviors/Behavior.cpp \
../behaviors/GotoWaypoint.cpp \
../behaviors/MoveForward.cpp \
../behaviors/ObstacleAvoid.cpp \
../behaviors/WaypointSelectionBehaviour.cpp 

OBJS += \
./behaviors/Behavior.o \
./behaviors/GotoWaypoint.o \
./behaviors/MoveForward.o \
./behaviors/ObstacleAvoid.o \
./behaviors/WaypointSelectionBehaviour.o 

CPP_DEPS += \
./behaviors/Behavior.d \
./behaviors/GotoWaypoint.d \
./behaviors/MoveForward.d \
./behaviors/ObstacleAvoid.d \
./behaviors/WaypointSelectionBehaviour.d 


# Each subdirectory must supply rules for building sources it contributes
behaviors/%.o: ../behaviors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


