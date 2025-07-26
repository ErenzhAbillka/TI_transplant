#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * @brief  ����������ź�PWM��ʼ��
  * @note   ��������ʹ�� GPIOB �� 12~15��PWM ͨ���� PWM_Init ��ʼ��
  * @param  ��
  * @retval ��
  */
void Motor_Init(void)
{
    // ���� GPIOB ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // ��ʼ�� PB12~PB15 Ϊ������������ڵ��������ƣ�
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // ��ʼ�� PWM�����ڵ���ٶȿ��ƣ�
    PWM_Init();
}

/**
  * @brief  ��������ת���뷽��
  * @param  Speed: �ٶ�ֵ����Χ -100 ~ +100����ֵ��ʾ��ת����ֵ��ʾ��ת��
  * @retval ��
  */
void Motor_leftSetSpeed(int8_t Speed)
{
    if (Speed >= 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_14);   // PB14 �ߵ�ƽ
        GPIO_ResetBits(GPIOB, GPIO_Pin_15); // PB15 �͵�ƽ -> ��ת
        PWM_SetLeftMotorPWM(Speed);            // ���� PWM ռ�ձȣ�ͨ��3��
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15); // PB15 �͵�ƽ
        GPIO_SetBits(GPIOB, GPIO_Pin_14);   // PB14 �ߵ�ƽ -> ��ת
        PWM_SetLeftMotorPWM(-Speed);           // ȡ������Ϊ PWM ֵ
    }
}

/**
  * @brief  �����ҵ��ת���뷽��
  * @param  Speed: �ٶ�ֵ����Χ -100 ~ +100����ֵ��ʾ��ת����ֵ��ʾ��ת��
  * @retval ��
  */
void Motor_rightSetSpeed(int8_t Speed)
{
    if (Speed >= 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_12);   // PB12 �ߵ�ƽ
        GPIO_ResetBits(GPIOB, GPIO_Pin_13); // PB13 �͵�ƽ -> ��ת
        PWM_SetRightMotorPWM(Speed);            // ���� PWM ռ�ձȣ�ͨ��4��
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_13); // PB13 �͵�ƽ
        GPIO_SetBits(GPIOB, GPIO_Pin_12);   // PB12 �ߵ�ƽ -> ��ת
        PWM_SetRightMotorPWM(-Speed);           // ȡ������Ϊ PWM ֵ
    }
}
