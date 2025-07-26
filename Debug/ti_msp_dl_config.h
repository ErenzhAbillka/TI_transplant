/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_WHEEL */
#define PWM_WHEEL_INST                                                     TIMA1
#define PWM_WHEEL_INST_IRQHandler                               TIMA1_IRQHandler
#define PWM_WHEEL_INST_INT_IRQN                                 (TIMA1_INT_IRQn)
#define PWM_WHEEL_INST_CLK_FREQ                                          2000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_WHEEL_C0_PORT                                             GPIOA
#define GPIO_PWM_WHEEL_C0_PIN                                     DL_GPIO_PIN_10
#define GPIO_PWM_WHEEL_C0_IOMUX                                  (IOMUX_PINCM21)
#define GPIO_PWM_WHEEL_C0_IOMUX_FUNC                 IOMUX_PINCM21_PF_TIMA1_CCP0
#define GPIO_PWM_WHEEL_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 0 */
#define GPIO_PWM_WHEEL_C0_CMPL_PORT                                        GPIOA
#define GPIO_PWM_WHEEL_C0_CMPL_PIN                                DL_GPIO_PIN_15
#define GPIO_PWM_WHEEL_C0_CMPL_IOMUX                             (IOMUX_PINCM37)
#define GPIO_PWM_WHEEL_C0_CMPL_IOMUX_FUNC        IOMUX_PINCM37_PF_TIMA1_CCP0_CMPL

/* GPIO defines for channel 1 */
#define GPIO_PWM_WHEEL_C1_PORT                                             GPIOA
#define GPIO_PWM_WHEEL_C1_PIN                                     DL_GPIO_PIN_11
#define GPIO_PWM_WHEEL_C1_IOMUX                                  (IOMUX_PINCM22)
#define GPIO_PWM_WHEEL_C1_IOMUX_FUNC                 IOMUX_PINCM22_PF_TIMA1_CCP1
#define GPIO_PWM_WHEEL_C1_IDX                                DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_WHEEL_C1_CMPL_PORT                                        GPIOA
#define GPIO_PWM_WHEEL_C1_CMPL_PIN                                DL_GPIO_PIN_16
#define GPIO_PWM_WHEEL_C1_CMPL_IOMUX                             (IOMUX_PINCM38)
#define GPIO_PWM_WHEEL_C1_CMPL_IOMUX_FUNC        IOMUX_PINCM38_PF_TIMA1_CCP1_CMPL




/* Defines for CAPTURE_0 */
#define CAPTURE_0_INST                                                   (TIMA0)
#define CAPTURE_0_INST_IRQHandler                               TIMA0_IRQHandler
#define CAPTURE_0_INST_INT_IRQN                                 (TIMA0_INT_IRQn)
#define CAPTURE_0_INST_LOAD_VALUE                                        (1249U)
/* GPIO defines for channel 0 */
#define GPIO_CAPTURE_0_C0_PORT                                             GPIOA
#define GPIO_CAPTURE_0_C0_PIN                                      DL_GPIO_PIN_0
#define GPIO_CAPTURE_0_C0_IOMUX                                   (IOMUX_PINCM1)
#define GPIO_CAPTURE_0_C0_IOMUX_FUNC                  IOMUX_PINCM1_PF_TIMA0_CCP0






/* Port definition for Pin Group Motor */
#define Motor_PORT                                                       (GPIOA)

/* Defines for leftDIR: GPIOA.17 with pinCMx 39 on package pin 10 */
#define Motor_leftDIR_PIN                                       (DL_GPIO_PIN_17)
#define Motor_leftDIR_IOMUX                                      (IOMUX_PINCM39)
/* Defines for leftENABLE: GPIOA.14 with pinCMx 36 on package pin 7 */
#define Motor_leftENABLE_PIN                                    (DL_GPIO_PIN_14)
#define Motor_leftENABLE_IOMUX                                   (IOMUX_PINCM36)
/* Defines for rightDIR: GPIOA.13 with pinCMx 35 on package pin 6 */
#define Motor_rightDIR_PIN                                      (DL_GPIO_PIN_13)
#define Motor_rightDIR_IOMUX                                     (IOMUX_PINCM35)
/* Defines for rightENABLE: GPIOA.12 with pinCMx 34 on package pin 5 */
#define Motor_rightENABLE_PIN                                   (DL_GPIO_PIN_12)
#define Motor_rightENABLE_IOMUX                                  (IOMUX_PINCM34)
/* Port definition for Pin Group findRoad */
#define findRoad_PORT                                                    (GPIOB)

/* Defines for PIN_0: GPIOB.22 with pinCMx 50 on package pin 21 */
#define findRoad_PIN_0_PIN                                      (DL_GPIO_PIN_22)
#define findRoad_PIN_0_IOMUX                                     (IOMUX_PINCM50)
/* Defines for PIN_1: GPIOB.21 with pinCMx 49 on package pin 20 */
#define findRoad_PIN_1_PIN                                      (DL_GPIO_PIN_21)
#define findRoad_PIN_1_IOMUX                                     (IOMUX_PINCM49)
/* Defines for PIN_2: GPIOB.20 with pinCMx 48 on package pin 19 */
#define findRoad_PIN_2_PIN                                      (DL_GPIO_PIN_20)
#define findRoad_PIN_2_IOMUX                                     (IOMUX_PINCM48)
/* Defines for PIN_3: GPIOB.19 with pinCMx 45 on package pin 16 */
#define findRoad_PIN_3_PIN                                      (DL_GPIO_PIN_19)
#define findRoad_PIN_3_IOMUX                                     (IOMUX_PINCM45)
/* Defines for PIN_4: GPIOB.18 with pinCMx 44 on package pin 15 */
#define findRoad_PIN_4_PIN                                      (DL_GPIO_PIN_18)
#define findRoad_PIN_4_IOMUX                                     (IOMUX_PINCM44)
/* Defines for PIN_5: GPIOB.17 with pinCMx 43 on package pin 14 */
#define findRoad_PIN_5_PIN                                      (DL_GPIO_PIN_17)
#define findRoad_PIN_5_IOMUX                                     (IOMUX_PINCM43)
/* Defines for PIN_6: GPIOB.16 with pinCMx 33 on package pin 4 */
#define findRoad_PIN_6_PIN                                      (DL_GPIO_PIN_16)
#define findRoad_PIN_6_IOMUX                                     (IOMUX_PINCM33)
/* Defines for PIN_7: GPIOB.15 with pinCMx 32 on package pin 3 */
#define findRoad_PIN_7_PIN                                      (DL_GPIO_PIN_15)
#define findRoad_PIN_7_IOMUX                                     (IOMUX_PINCM32)
/* Port definition for Pin Group Key */
#define Key_PORT                                                         (GPIOB)

/* Defines for Key1: GPIOB.14 with pinCMx 31 on package pin 2 */
#define Key_Key1_PIN                                            (DL_GPIO_PIN_14)
#define Key_Key1_IOMUX                                           (IOMUX_PINCM31)
/* Defines for PIN_9: GPIOB.13 with pinCMx 30 on package pin 1 */
#define Key_PIN_9_PIN                                           (DL_GPIO_PIN_13)
#define Key_PIN_9_IOMUX                                          (IOMUX_PINCM30)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_WHEEL_init(void);
void SYSCFG_DL_CAPTURE_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
