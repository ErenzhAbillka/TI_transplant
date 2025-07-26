#include "stm32f10x.h"  // Device header

/**
  * @brief  ���ֱ�������ʼ����ʹ�� TIM1��PA8-CH1��PA9-CH2��
  * @note   ʹ�ñ������ӿ�ģʽ����ȡ��������������
  *         PA8 �� TIM1_CH1��PA9 �� TIM1_CH2
  * @param  ��
  * @retval ��
  */
void Encoder_Right_Init(void)
{
    /* 1. ����ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);      // ���� TIM1 ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     // ���� GPIOA ʱ��

    /* 2. ���� GPIOA8/A9 Ϊ�������루������ A/B �ࣩ */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;             // ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;    // PA8:CH1, PA9:CH2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 3. ���ö�ʱ���������� */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;      // ʱ�Ӳ���Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 65535;                    // ������ֵ��16λ��
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;                     // ��Ԥ��Ƶ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            // �ظ������������߼���ʱ��ʹ��
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    /* 4. ���벶���˲������ã�CH1 & CH2�� */
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);      // ��ʼ���ṹ��Ĭ��ֵ
    TIM_ICInitStructure.TIM_ICFilter = 0x0F;     // ����˲���������

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);

    /* 5. �������ӿ�ģʽ���� */
    TIM_EncoderInterfaceConfig(
        TIM1,
        TIM_EncoderMode_TI12,          // ������ģʽ��˫ͨ��
        TIM_ICPolarity_Rising,         // CH1 ������
        TIM_ICPolarity_Rising          // CH2 ������
    );

    /* 6. �����������������ʱ�� */
    TIM_SetCounter(TIM1, 0);      // ��ʼ�� CNT Ϊ 0
    TIM_Cmd(TIM1, ENABLE);        // ���� TIM1
}

/**
  * @brief  ��ȡ���ֱ�����������ֵ��TIM1��
  * @note   ÿ�ε��ú���Զ����� CNT
  * @param  ��
  * @retval int16_t ������������-32768 ~ 32767��
  */
int16_t Encoder_Right_GetDelta(void)
{
    int16_t delta = (int16_t)TIM_GetCounter(TIM1);  // ��ȡ CNT ֵ
    TIM_SetCounter(TIM1, 0);                        // ���� CNT
    return delta;
}

