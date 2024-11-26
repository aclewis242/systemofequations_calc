################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Context/CalculatorContext.cpp 

OBJS += \
./Context/CalculatorContext.o 

CPP_DEPS += \
./Context/CalculatorContext.d 


# Each subdirectory must supply rules for building sources it contributes
Context/%.o: ../Context/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


