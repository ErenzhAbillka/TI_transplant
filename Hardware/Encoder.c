#include "stm32f10x.h"  // Device header

/**
  * @brief  ���ֱ�������ʼ����TIM3��PA6-CH1��PA7-CH2��
  * @note   ʹ�ñ������ӿ�ģʽ����ȡ˫·�������������������
  *         PA6 �� TIM3_CH1��PA7 �� TIM3_CH2
  * @param  ��
  * @retval ��
  */
void Encoder_Left_Init(void)
{
    /* 1. ����ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);      // ���� TIM3 ��ʱ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     // ���� GPIOA ʱ��

    /* 2. ��ʼ�� GPIOA6/A7 Ϊ��������ģʽ�����ӱ����� A/B �ࣩ */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;             // ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;    // PA6/PA7 ��Ӧ TIM3_CH1/CH2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 3. ��ʱ��������Ԫ���� */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;      // ʱ�Ӳ���Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 65535;                    // �Զ���װֵ�����ֵ��16λ��
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;                     // ��Ԥ��Ƶ����Чϵͳ��Ƶֱ��������
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            // �ظ����������߼���ʱ��ʹ��
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    /* 4. ���벶�����ã�CH1/CH2�����˲��� */
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);                // �ȳ�ʼ��ΪĬ��ֵ

    TIM_ICInitStructure.TIM_ICFilter = 0x0F;               // ��������˲���15�����˳�����

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;       // ���� CH1
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;       // ���� CH2
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    /* 5. ���ñ������ӿ�ģʽ */
    TIM_EncoderInterfaceConfig(
        TIM3,
        TIM_EncoderMode_TI12,          // ʹ�� CH1 �� CH2 ˫ͨ��������ģʽ
        TIM_ICPolarity_Rising,         // ������
        TIM_ICPolarity_Rising          // ������
    );

    /* 6. �����������������ʱ�� */
    TIM_SetCounter(TIM3, 0);  // ��ʼ�� CNT Ϊ 0
    TIM_Cmd(TIM3, ENABLE);    // ���� TIM3
}

/**
  * @brief  ��ȡ���ֱ�����������ֵ��TIM3��
  * @note   ÿ�ε��û��Զ����� TIM3 �ļ�����
  * @param  ��
  * @retval int16_t ����������-32768 ~ 32767��
  */
int16_t Encoder_Left_GetDelta(void)
{
    int16_t delta = (int16_t)TIM_GetCounter(TIM3);  // ��ȡ��ǰ CNT
    TIM_SetCounter(TIM3, 0);                        // ���� CNT��׼����һ�ζ�ȡ
    return delta;
}
