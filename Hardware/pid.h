#ifndef __PID_H
#define __PID_H


typedef struct
{
    float SetValue; // ����ֵ �ο�ֵ
    float ActValue; // ʵ��ֵ
    float KP; // ��������
    float KI; // ��������
    float KD; // ΢������
    float ek; // �������
    float ek_1; // ��һ��
    float ek_2; // ���ϴ�
    float ek_sum; // ����ۻ�
    float Sum_max; // ����ۺ�����
    float Sum_min; // ����ۺ�����
    float PIDmax; // max limit
    float PIDmin; // min limit
    float PIDout; // output
}PID;

extern PID speed;//�ٶ�
extern PID Angle;//�Ƕ�
//extern PID Deviation;//���������Ჹ����

void PID_Init(void);
float PID_Control_Inc(PID* pid,int flag);
float PID_Control_Pos(PID* pid,int flag);
float Speed_PID_Count(float actvalue_sudu,float expected_sudu);
float Angle_PID_Count(float actvalue_angle,float expected_angle);
#endif