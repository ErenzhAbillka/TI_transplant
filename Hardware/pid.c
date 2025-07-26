#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "pid.h"
PID speed = {0};
//PID Devation = {0};
PID Angle = {0};

float out_sudu = 0.0;
float out_angle = 0.0;


void PID_Init(void)
{
	speed.KP = 0.0;
	speed.KI =0.0;
  speed.KD = 0.0;
	
//	Deviation.KP = 0.0;
//	Deviation.KI = 0.0;
//	Deviation.KD = 0.0;
	
	Angle.KP = 0.0;
	Angle.KI = 0.0;
	Angle.KD = 0.0;
	
	
}

float PID_Control_Inc(PID* pid,int flag)  //����ʽPID
{
    float inc;

    pid->ek = pid->SetValue - pid->ActValue;
    inc = pid->KP * (pid->ek - pid->ek_1) + pid->KI * pid->ek+pid->KD*(pid->ek-2*pid->ek_1+pid->ek_2);
    
    pid->ek_2 = pid->ek_1; 
    pid->ek_1 = pid->ek; 

    if(flag == 1)
    {
        if(inc > pid->PIDmax)
            inc = pid->PIDmax;
        if(inc < pid->PIDmin)
            inc = pid->PIDmin;
    }
    pid->PIDout += inc;
    return inc;
}


float PID_Control_Pos(PID* pid,int flag) //λ��ʽPID
{
    float Pos ;

    pid->ek = pid->SetValue - pid->ActValue;
    pid->ek_sum += pid->ek;


    Pos = pid->KP * pid->ek + pid->KI * pid->ek_sum + pid->KD * (pid->ek - pid->ek_1);

    pid->ek_2 = pid->ek_1; 
    pid->ek_1 = pid->ek; 

    if(flag == 1)
    {
        if(Pos > pid->PIDmax)
            Pos = pid->PIDmax;
        if(Pos < pid->PIDmin)
            Pos = pid->PIDmin;
    }
    pid->PIDout = Pos;
	
    return pid->PIDout;
}


//����ʽ
float a=0,b=0;
float Speed_PID_Count(float actvalue_sudu,float expected_sudu)//�ٶȻ�
{
    speed.ActValue= actvalue_sudu;
    speed.SetValue=expected_sudu;
	  a=speed.ek_1;
    speed.ek=speed.SetValue-speed.ActValue;

    speed.PIDout+=(speed.ek*speed.KP+(speed.ek-speed.ek_1)*speed.KD)+speed.KI*(speed.ek-2*speed.ek_1+speed.ek_2);
	speed.ek_2=speed.ek_1;
	speed.ek_1=speed.ek;
    if(speed.PIDout < -100)   //����޷������������Сռ�ձ�
    speed.PIDout = -100;
    if(speed.PIDout> 100)
    speed.PIDout = 100;
     out_sudu =  speed.PIDout;
		return out_sudu;
}



//����ʽ

float Angle_PID_Count(float actvalue_angle,float expected_angle)  //�ǶȻ�
{	
    Angle.SetValue  = expected_angle ;
    Angle.ActValue  = actvalue_angle;
    PID_Control_Pos(&Angle,1);
//	if(Angle.PIDout > 100)
//		{Angle.PIDout =100;}
//        if(Angle.PIDout <-100)
//		{ Angle.PIDout =-100;}
		
		out_angle = Angle.PIDout;
		return out_angle;
}