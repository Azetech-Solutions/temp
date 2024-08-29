################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB/Core/Src/usbh_conf.c \
../USB/Core/Src/usbh_core.c \
../USB/Core/Src/usbh_ctlreq.c \
../USB/Core/Src/usbh_ioreq.c \
../USB/Core/Src/usbh_pipes.c 

OBJS += \
./USB/Core/Src/usbh_conf.o \
./USB/Core/Src/usbh_core.o \
./USB/Core/Src/usbh_ctlreq.o \
./USB/Core/Src/usbh_ioreq.o \
./USB/Core/Src/usbh_pipes.o 

C_DEPS += \
./USB/Core/Src/usbh_conf.d \
./USB/Core/Src/usbh_core.d \
./USB/Core/Src/usbh_ctlreq.d \
./USB/Core/Src/usbh_ioreq.d \
./USB/Core/Src/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
USB/Core/Src/%.o USB/Core/Src/%.su USB/Core/Src/%.cyclo: ../USB/Core/Src/%.c USB/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H503xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"D:/Mohan/Class/STM_32/CUBE_IDE/usbHost_try/USB/Class/CDC/Inc" -I"D:/Mohan/Class/STM_32/CUBE_IDE/usbHost_try/USB/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB-2f-Core-2f-Src

clean-USB-2f-Core-2f-Src:
	-$(RM) ./USB/Core/Src/usbh_conf.cyclo ./USB/Core/Src/usbh_conf.d ./USB/Core/Src/usbh_conf.o ./USB/Core/Src/usbh_conf.su ./USB/Core/Src/usbh_core.cyclo ./USB/Core/Src/usbh_core.d ./USB/Core/Src/usbh_core.o ./USB/Core/Src/usbh_core.su ./USB/Core/Src/usbh_ctlreq.cyclo ./USB/Core/Src/usbh_ctlreq.d ./USB/Core/Src/usbh_ctlreq.o ./USB/Core/Src/usbh_ctlreq.su ./USB/Core/Src/usbh_ioreq.cyclo ./USB/Core/Src/usbh_ioreq.d ./USB/Core/Src/usbh_ioreq.o ./USB/Core/Src/usbh_ioreq.su ./USB/Core/Src/usbh_pipes.cyclo ./USB/Core/Src/usbh_pipes.d ./USB/Core/Src/usbh_pipes.o ./USB/Core/Src/usbh_pipes.su

.PHONY: clean-USB-2f-Core-2f-Src

