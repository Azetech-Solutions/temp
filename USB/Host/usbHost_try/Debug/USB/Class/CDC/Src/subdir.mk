################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB/Class/CDC/Src/usb_host.c \
../USB/Class/CDC/Src/usbh_cdc.c 

OBJS += \
./USB/Class/CDC/Src/usb_host.o \
./USB/Class/CDC/Src/usbh_cdc.o 

C_DEPS += \
./USB/Class/CDC/Src/usb_host.d \
./USB/Class/CDC/Src/usbh_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
USB/Class/CDC/Src/%.o USB/Class/CDC/Src/%.su USB/Class/CDC/Src/%.cyclo: ../USB/Class/CDC/Src/%.c USB/Class/CDC/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H503xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"D:/Mohan/Class/STM_32/CUBE_IDE/usbHost_try/USB/Class/CDC/Inc" -I"D:/Mohan/Class/STM_32/CUBE_IDE/usbHost_try/USB/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB-2f-Class-2f-CDC-2f-Src

clean-USB-2f-Class-2f-CDC-2f-Src:
	-$(RM) ./USB/Class/CDC/Src/usb_host.cyclo ./USB/Class/CDC/Src/usb_host.d ./USB/Class/CDC/Src/usb_host.o ./USB/Class/CDC/Src/usb_host.su ./USB/Class/CDC/Src/usbh_cdc.cyclo ./USB/Class/CDC/Src/usbh_cdc.d ./USB/Class/CDC/Src/usbh_cdc.o ./USB/Class/CDC/Src/usbh_cdc.su

.PHONY: clean-USB-2f-Class-2f-CDC-2f-Src

