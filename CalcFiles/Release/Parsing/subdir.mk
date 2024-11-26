################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Parsing/ExpressionBuilder.cpp \
../Parsing/InfixToPostfix.cpp \
../Parsing/ParseInputToTokens.cpp 

OBJS += \
./Parsing/ExpressionBuilder.o \
./Parsing/InfixToPostfix.o \
./Parsing/ParseInputToTokens.o 

CPP_DEPS += \
./Parsing/ExpressionBuilder.d \
./Parsing/InfixToPostfix.d \
./Parsing/ParseInputToTokens.d 


# Each subdirectory must supply rules for building sources it contributes
Parsing/%.o: ../Parsing/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


