################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS

GEN_OPTS__FLAG := @"./device.opt" 
GEN_CMDS__FLAG := -Wl,-l"./device_linker.cmd" 

ORDERED_OBJS += \
"./empty.o" \
"./ti_msp_dl_config.o" \
"./startup_mspm0g350x_ticlang.o" \
"./Hardware/Buzzer.o" \
"./Hardware/DHT11.o" \
"./Hardware/Encoder.o" \
"./Hardware/Encoder1.o" \
"./Hardware/HCSR04.o" \
"./Hardware/Key.o" \
"./Hardware/LED.o" \
"./Hardware/MPU6050.o" \
"./Hardware/Motor.o" \
"./Hardware/OLED.o" \
"./Hardware/PWM.o" \
"./Hardware/Timer.o" \
"./Hardware/car.o" \
"./Hardware/inv_mpu.o" \
"./Hardware/inv_mpu_dmp_motion_driver.o" \
"./Hardware/kalman.o" \
"./Hardware/mpuiic.o" \
"./Hardware/pid.o" \
"./Hardware/speed_filter.o" \
"./Hardware/xunji.o" \
$(GEN_CMDS__FLAG) \
-Wl,-ldevice.cmd.genlibs \
-Wl,-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Hardware/subdir_vars.mk
-include subdir_rules.mk
-include Hardware/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
TI_transplant.out 

EXE_OUTPUTS__QUOTED += \
"TI_transplant.out" 


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "TI_transplant.out"

# Tool invocations
TI_transplant.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"/Applications/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang" @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -gdwarf-3 -Wl,-m"TI_transplant.map" -Wl,-i"/Users/suki/ti/mspm0_sdk_2_05_01_00/source" -Wl,-i"/Users/suki/myProject/ti_Project/TI_transplant" -Wl,-i"/Users/suki/myProject/ti_Project/TI_transplant/Debug/syscfg" -Wl,-i"/Applications/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/lib" -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="TI_transplant_linkInfo.xml" -Wl,--rom_model -o "TI_transplant.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "empty.o" "ti_msp_dl_config.o" "startup_mspm0g350x_ticlang.o" "Hardware/Buzzer.o" "Hardware/DHT11.o" "Hardware/Encoder.o" "Hardware/Encoder1.o" "Hardware/HCSR04.o" "Hardware/Key.o" "Hardware/LED.o" "Hardware/MPU6050.o" "Hardware/Motor.o" "Hardware/OLED.o" "Hardware/PWM.o" "Hardware/Timer.o" "Hardware/car.o" "Hardware/inv_mpu.o" "Hardware/inv_mpu_dmp_motion_driver.o" "Hardware/kalman.o" "Hardware/mpuiic.o" "Hardware/pid.o" "Hardware/speed_filter.o" "Hardware/xunji.o" 
	-$(RM) "empty.d" "ti_msp_dl_config.d" "startup_mspm0g350x_ticlang.d" "Hardware/Buzzer.d" "Hardware/DHT11.d" "Hardware/Encoder.d" "Hardware/Encoder1.d" "Hardware/HCSR04.d" "Hardware/Key.d" "Hardware/LED.d" "Hardware/MPU6050.d" "Hardware/Motor.d" "Hardware/OLED.d" "Hardware/PWM.d" "Hardware/Timer.d" "Hardware/car.d" "Hardware/inv_mpu.d" "Hardware/inv_mpu_dmp_motion_driver.d" "Hardware/kalman.d" "Hardware/mpuiic.d" "Hardware/pid.d" "Hardware/speed_filter.d" "Hardware/xunji.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

