################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../InitEnvironment.cpp \
../Location.cpp \
../Manager.cpp \
../main.cpp \
../robot.cpp 

OBJS += \
./InitEnvironment.o \
./Location.o \
./Manager.o \
./main.o \
./robot.o 

CPP_DEPS += \
./InitEnvironment.d \
./Location.d \
./Manager.d \
./main.d \
./robot.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


