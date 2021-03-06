################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../zephyr/drivers/flash/flash_stm32.c \
../zephyr/drivers/flash/flash_stm32f1x.c 

OBJS += \
./zephyr/drivers/flash/flash_stm32.o \
./zephyr/drivers/flash/flash_stm32f1x.o 

C_DEPS += \
./zephyr/drivers/flash/flash_stm32.d \
./zephyr/drivers/flash/flash_stm32f1x.d 


# Each subdirectory must supply rules for building sources it contributes
zephyr/drivers/flash/%.o: ../zephyr/drivers/flash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32F103xB -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"../freertos-code\FreeRTOS\Source\include" -I"../freertos-code\FreeRTOS\Source\portable\GCC\ARM_CM3" -I../CMSIS_RTOS -I"../zephyr\include" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


