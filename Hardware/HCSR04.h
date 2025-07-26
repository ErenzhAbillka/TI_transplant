#ifndef __HCSR04_H
#define __HCSR04_H



// �����СPWM���壨������ĵ����������������
#define MAX_PWM     1000
#define MIN_PWM     -1000

// Ŀ����루��λ��mm��
#define TARGET_DISTANCE_MM 200.0f

// PID�ṹ�嶨��
typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    float prev_error;
    float integral;
} PID_TypeDef;

// �ⲿ��������
extern PID_TypeDef Distance_PID;
extern float base_v;

// ��������
float constrain_float(float value, float min, float max);
void Distance_PID_Control(void);
void HC_SR04_Init(void);
int16_t sonar_mm(void);
float sonar(void);

#endif
