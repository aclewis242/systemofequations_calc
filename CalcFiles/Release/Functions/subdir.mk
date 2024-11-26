################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Functions/FunctionModule.cpp 

OBJS += \
./Functions/FunctionModule.o 

CPP_DEPS += \
./Functions/FunctionModule.d 


# Each subdirectory must supply rules for building sources it contributes
Functions/%.o: ../Functions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


