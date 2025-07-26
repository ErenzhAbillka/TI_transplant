################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/Users/suki/myProject/ti_Project/TI_transplant" -I"/Users/suki/myProject/ti_Project/TI_transplant/Debug" -I"/Users/suki/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"/Users/suki/ti/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"Hardware/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


