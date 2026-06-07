################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/kth59/.stm32cubeaistudio/workspace/ANN_GMPPT/.ai/run/run-1/Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.c 

OBJS += \
./Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.o 

C_DEPS += \
./Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.o: C:/Users/kth59/.stm32cubeaistudio/workspace/ANN_GMPPT/.ai/run/run-1/Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.c Drivers/BSP/STM32N6xx_Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32N657xx -c -I../../../FSBL/Core/Inc -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/ST/STM32_ExtMem_Manager -I../../../Middlewares/ST/STM32_ExtMem_Manager/boot -I../../../Middlewares/ST/STM32_ExtMem_Manager/sal -I../../../Middlewares/ST/STM32_ExtMem_Manager/nor_sfdp -I../../../Middlewares/ST/STM32_ExtMem_Manager/psram -I../../../Middlewares/ST/STM32_ExtMem_Manager/sdcard -I../../../Middlewares/ST/STM32_ExtMem_Manager/user -I../../../Drivers/CMSIS/Include -I../../../Drivers/BSP/STM32N6xx_Nucleo -I../../../Drivers/BSP/Components/mx25um51245g -I../../../Drivers/STM32N6xx_HAL_Driver/Src -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32N6xx_Nucleo

clean-Drivers-2f-BSP-2f-STM32N6xx_Nucleo:
	-$(RM) ./Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.cyclo ./Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.d ./Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.o ./Drivers/BSP/STM32N6xx_Nucleo/stm32n6xx_nucleo_xspi.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32N6xx_Nucleo

