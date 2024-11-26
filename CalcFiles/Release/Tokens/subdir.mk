################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Tokens/Token.cpp 

OBJS += \
./Tokens/Token.o 

CPP_DEPS += \
./Tokens/Token.d 


# Each subdirectory must supply rules for building sources it contributes
Tokens/%.o: ../Tokens/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


