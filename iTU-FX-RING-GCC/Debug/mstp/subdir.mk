################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../mstp/stp.cpp \
../mstp/stp_base_types.cpp \
../mstp/stp_bpdu.cpp \
../mstp/stp_log.cpp \
../mstp/stp_md5.cpp 

OBJS += \
./mstp/stp.o \
./mstp/stp_base_types.o \
./mstp/stp_bpdu.o \
./mstp/stp_log.o \
./mstp/stp_md5.o 

CPP_DEPS += \
./mstp/stp.d \
./mstp/stp_base_types.d \
./mstp/stp_bpdu.d \
./mstp/stp_log.d \
./mstp/stp_md5.d 


# Each subdirectory must supply rules for building sources it contributes
mstp/%.o: ../mstp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wall -Wextra  -g3 -DUSE_FULL_ASSERT -DSTM32F407xx -DUSE_HAL_DRIVER -I../Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -I"../lib60870-C\config" -I"../lib60870-C\src\common\inc" -I"../lib60870-C\src\hal\inc" -I"../lib60870-C\src\inc\api" -I"../lib60870-C\src\inc\internal" -I"../FreeModbus\modbus\include" -I"../FreeModbus\modbus\rtu" -I"../FreeModbus\port" -I../mstp-lib -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

