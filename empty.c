/*
 * Copyright (c) 2021, Texas Instruments Incorporated
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

#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();

    while (1) {
    }
}

/*=======================================================================*/

/*
#include "stm32f10x.h"          // STM32标准库头文件
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
//#include "Encoder.h"            // 左轮编码器接口头文件
//#include "Encoder1.h"           // 右轮编码器接口头文件
#include "Motor.h"
#include "car.h"
//#include "MPU6050.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
#include "xunji.h"              // 循迹传感器相关头文件
#include "key.h"
#include "led.h"
#include "Buzzer.h"
#include "pid.h"
#include "speed_filter.h"       // 速度滤波接口
#include "HCSR04.h"       // 速度滤波接口

#define BASE_SPEED 30
#define MAX_SPEED 40
//// 宏定义部分，根据你的硬件参数配置
//#define WHEEL_CIRCUMFERENCE 0.188f  // 轮子周长，单位米，示例为直径0.06m的轮子
//#define ENCODER_PPR 500             // 编码器每转脉冲数（Pulses Per Revolution）
//#define SAMPLE_TIME 0.01f           // 采样时间，单位秒（对应定时器中断周期，比如10ms）

// 全局变量
int sensors1[8];                   // 传感器状态缓存数组
int stop_flag = 0;                 // 停车标志计数，用于判断是否停车
int KeyNum = 0;                   // 按键编号
int confirm = 0;                   // 驱动确认标志，1使能驱动，0禁止
int MODE = 0;                     // 工作模式变量（备用）
int num = 0;                      // 按键切换变量

typedef enum {
    STRAIGHT,
    IN_CURVE
} TrackState;

TrackState track_state = STRAIGHT;
float base_v = BASE_SPEED;  // 基础速度
// 状态机
void update_speed_state(void) {
    static uint8_t curve_flag = 0;  // 标记是否已加速
    
    if (track_state == STRAIGHT) {
        if (Trackn >= 3 && Trackn <= 127) {  // 进入弯道
            track_state = IN_CURVE;
            if (!curve_flag) {  // 首次进入才加速
                base_v = MAX_SPEED;
                curve_flag = 1;
            }
        }
    } 
    else {  // IN_CURVE状态
        if (Trackn > 3 && Trackn < 127) {  // 离开弯道
            track_state = STRAIGHT;
            base_v = BASE_SPEED;  // 恢复原速
            curve_flag = 0;       // 重置标记
        }
    }
}


int main(void)
{
    // 初始化各硬件模块
    OLED_Init();            // OLED显示屏初始化
   // Encoder_Left_Init();    // 左轮编码器初始化
   // Encoder_Right_Init();   // 右轮编码器初始化
    Motor_Init();           // 电机驱动初始化
    Xunji_Init();           // 循迹传感器初始化
    Key_Init();             // 按键初始化
	  //mpu_dmp_init();         // MPU6050传感器初始化（含DMP）
	  Timer_Init();           // 定时器初始化（含中断配置）
  //  LED_Init();             // 指示灯初始化
   // Buzzer_Init();          // 蜂鸣器初始化
    //PID_Init();             // PID控制参数初始化

	while (1)
	{
					
		read_sensors(sensors1);//读取传感器的值
		OLED_ShowNum(1,1,Trackn,3);//
	//	OLED_ShowString(2,1,track_state);//
	 // 停车
		  int all_black = 0;
        if(sensors1[0]== 0&&sensors1[1]== 0&&sensors1[2]== 0&&sensors1[3]== 0&&sensors1[4]== 0&&sensors1[5]== 0
					&&sensors1[6]== 0&&sensors1[7]== 0) { 					// 根据实际传感器逻辑调整 
            all_black = 1;
        }
    if(all_black) {
        stop_flag++;
        Delay_ms(100); // 防抖
    }
		OLED_ShowNum(1,5, stop_flag,3);//模式显示
		//单弯道加速
		update_speed_state();
		//按键检测
		KeyNum = Key_GetNum();
		 if(KeyNum == 1)
		 {
			 MODE++;
			 MODE%=5;
		 }
		 if(KeyNum == 2)
		 {
			 num ++;
			 if(num>2)
			 {
				 num = 1;
			 }
		 }
		
	if(num == 1)
	{
		confirm = 1; //电机驱动标志位 1为驱动，0为暂停
		OLED_ShowString(2,1,"OK");
	}
	if(num == 2)
	{
		confirm = 0;
		OLED_ShowString(2,1,"NO");
	}
	
  }
}



void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)		//判断是否是TIM4的更新事件触发的中断
	{
		update_redSensor();//更新传感器的值
	  //Key_Tick();//非阻塞式按键
		if(stop_flag >= 2) {
    Motor_leftSetSpeed(0);
    Motor_rightSetSpeed(0);
} else {
    int left, right;
    trait(&left, &right, base_v);
    Motor_leftSetSpeed(right);
    Motor_rightSetSpeed(left);
			
				TIM_ClearITPendingBit(TIM4, TIM_IT_Update);			//清除TIM4更新事件的中断标志位	
	}
}
}
*/