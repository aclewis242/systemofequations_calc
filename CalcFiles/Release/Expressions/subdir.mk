################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Expressions/Expression.cpp \
../Expressions/ExpressionModule.cpp 

OBJS += \
./Expressions/Expression.o \
./Expressions/ExpressionModule.o 

CPP_DEPS += \
./Expressions/Expression.d \
./Expressions/ExpressionModule.d 


# Each subdirectory must supply rules for building sources it contributes
Expressions/%.o: ../Expressions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


