#ifndef __XUNJI_H
#define __XUNJI_H

#include "stm32f10x.h"

// ������״̬���飬�ⲿ����
extern int red_sensors[8];

// ���������״̬�����ͣ�
extern int Trackn;

// ������״̬�仯��־��������/�½��أ�
extern int comePointFlag;
//extern int wandao_line;
/**
 * @brief �޷���������ֵ֤��[min, max]��Χ��
 * @param value ����ֵ
 * @param min ��Сֵ
 * @param max ���ֵ
 * @return �޷����ֵ
 */
int constrain(int value, int min, int max);

/**
 * @brief ��ʼ��ѭ��������GPIO��
 */
void Xunji_Init(void);

/**
 * @brief ��ȡ8·ѭ��������״̬�����´���������
 * @param read_senors ָ�򳤶�Ϊ8���������飬���ڴ洢��ȡ��״̬
 */
void read_sensors(int* read_senors);

/**
 * @brief ���º��⴫����״̬�����״̬����
 */
void update_redSensor(void);

/**
 * @brief С��ѭ�������ƺ���������PID���ڵ���ٶ�
 * @param Motor_leftSetSpeed ָ�������ٶȱ�����ָ�루PWMֵ��
 * @param Motor_rightSetSpeed ָ���ҵ���ٶȱ�����ָ�루PWMֵ��
 * @param base_v �����ٶȣ�������
 */
void trait(int* Motor_leftSetSpeed, int* Motor_rightSetSpeed, int base_v);

#endif /* __XUNJI_H */
