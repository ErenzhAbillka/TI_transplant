#include "stm32f10x.h"                  // Device header
#include "kalman.h"
#include "MPU6050.h"
#include "Math.h"
//卡尔曼解算法库
int16_t AXX,AYY,AZZ,GXX,GYY,GZZ;
short aacx,aacy,aacz;		//加速度传感器原始数据 
short gyrox,gyroy,gyroz;	//陀螺仪原始数据 
float temperature;			//陀螺仪温度数据
float Accel_x;	     		//X轴加速度值暂存
float Accel_y;	    		//Y轴加速度值暂存
float Accel_z;	     		//Z轴加速度值暂存
float Gyro_x;				//X轴陀螺仪数据暂存
float Gyro_y;        	//Y轴陀螺仪数据暂存
float Gyro_z;		 		//Z轴陀螺仪数据暂存	
float Angle_x_temp;  		//由加速度计算的x倾斜角度
float Angle_y_temp;  		//由加速度计算的y倾斜角度
float Angle_z_temp;  		//由加速度计算的y倾斜角度
float Angle_X_Final; 		//X最终倾斜角度
float Angle_Y_Final; 		//Y最终倾斜角度
float Angle_Z_Final; 		//Y最终倾斜角度
//角度计算
void Angle_Calcu(void)	 
{

	MPU6050_GetData(&AXX, &AYY, &AZZ,&GXX,&GYY,&GZZ);
	float accx,accy,accz;//三方向角加速度值
	Accel_x = AXX; //x轴加速度值获取
	Accel_y = AYY; //y轴加速度值获取
	Accel_z = AZZ; //z轴加速度值获取
	Gyro_x  = GXX;  //x轴陀螺仪值获取
	Gyro_y  = GYY;  //y轴陀螺仪值获取
	Gyro_z  = GZZ;  //z轴陀螺仪值获取
	aacx = Accel_x;//x轴加速度值暂存
	aacy = Accel_y;//y轴加速度值暂存
	aacz = Accel_z;//z轴加速度值暂存
	gyrox = Gyro_x;//x轴陀螺仪值暂存
	gyroy = Gyro_y;//y轴陀螺仪值暂存
	gyroz = Gyro_z;//z轴陀螺仪值暂存 
	
	//角加速度原始值处理过程	
	//加速度传感器配置寄存器0X1C内写入0x01,设置范围为±2g。换算关系：2^16/4 = 16384LSB/g
	if(Accel_x<32764) accx=Accel_x/16384;//计算x轴加速度
	else              accx=1-(Accel_x-49152)/16384;
	if(Accel_y<32764) accy=Accel_y/16384;//计算y轴加速度
	else              accy=1-(Accel_y-49152)/16384;
	if(Accel_z<32764) accz=Accel_z/16384;//计算z轴加速度
	else              accz=1-(Accel_z-49152)/16384;
	//加速度反正切公式计算三个轴和水平面坐标系之间的夹角
	Angle_x_temp=(atan(accy/accz))*180/3.14;
	Angle_y_temp=(atan(accx/accz))*180/3.14;
  Angle_z_temp=(atan(accx/accy))*180/3.14;
	//判断计算后角度的正负号											
	if(Accel_x<32764) Angle_x_temp = +Angle_x_temp;
	if(Accel_x>32764) Angle_x_temp = -Angle_x_temp;
	if(Accel_y<32764) Angle_y_temp = +Angle_y_temp;
	if(Accel_y>32764) Angle_y_temp = -Angle_y_temp;
	if(Accel_z<32764) Angle_z_temp = +Angle_z_temp;
	if(Accel_z>32764) Angle_z_temp = -Angle_z_temp;
	
	//角速度原始值处理过程
	//陀螺仪配置寄存器0X1B内写入0x18，设置范围为2000deg/s。换算关系：2^16/4000=16.4LSB/(°/S)
	////计算角速度
	if(Gyro_x<32768) Gyro_x=-(Gyro_x/16.4);
	if(Gyro_x>32768) Gyro_x=+(65535-Gyro_x)/16.4;
	if(Gyro_y<32768) Gyro_y=-(Gyro_y/16.4);
	if(Gyro_y>32768) Gyro_y=+(65535-Gyro_y)/16.4;
	if(Gyro_z<32768) Gyro_z=-(Gyro_z/16.4);
	if(Gyro_z>32768) Gyro_z=+(65535-Gyro_z)/16.4;
	
	Kalman_Filter_X(Angle_x_temp,Gyro_x);  //卡尔曼滤波计算X倾角
	Kalman_Filter_Y(Angle_y_temp,Gyro_y);  //卡尔曼滤波计算Y倾角
  Kalman_Filter_Z(Angle_z_temp,Gyro_z);  //卡尔曼滤波计算z倾角		
} 


//卡尔曼参数		
float Q_angle = 0.001;		//角度数据置信度，角度噪声的协方差
float Q_gyro  = 0.003;		//角速度数据置信度，角速度噪声的协方差  
float R_angle = 0.5;		//加速度计测量噪声的协方差
float dt      = 0.02;		//滤波算法计算周期，由定时器定时20ms
char  C_0     = 1;			//H矩阵值
float Q_bias, Angle_err;	//Q_bias:陀螺仪的偏差  Angle_err:角度偏量 
float PCt_0, PCt_1, E;		//计算的过程量
float K_0, K_1, t_0, t_1;	//卡尔曼增益  K_0:用于计算最优估计值  K_1:用于计算最优估计值的偏差 t_0/1:中间变量
float P[4] ={0,0,0,0};	//过程协方差矩阵的微分矩阵，中间变量
float PP[2][2] = { { 1, 0 },{ 0, 1 } };//过程协方差矩阵P

void Kalman_Filter_X(float Accel,float Gyro) //卡尔曼函数		
{
	//步骤一，先验估计
	//公式：X(k|k-1) = AX(k-1|k-1) + BU(k)
	//X = (Angle,Q_bias)
	//A(1,1) = 1,A(1,2) = -dt
	//A(2,1) = 0,A(2,2) = 1
	Angle_X_Final += (Gyro - Q_bias) * dt; //状态方程,角度值等于上次最优角度加角速度减零漂后积分
	
	//步骤二，计算过程协方差矩阵的微分矩阵
	//公式：P(k|k-1)=AP(k-1|k-1)A^T + Q 
	//Q(1,1) = cov(Angle,Angle)	Q(1,2) = cov(Q_bias,Angle)
	//Q(2,1) = cov(Angle,Q_bias)	Q(2,2) = cov(Q_bias,Q_bias)
	P[0]= Q_angle - PP[0][1] - PP[1][0];
	P[1]= -PP[1][1];// 先验估计误差协方差
	P[2]= -PP[1][1];
	P[3]= Q_gyro;
	PP[0][0] += P[0] * dt;   
	PP[0][1] += P[1] * dt;   
	PP[1][0] += P[2] * dt;
	PP[1][1] += P[3] * dt;	
	Angle_err = Accel - Angle_X_Final;	//Z(k)先验估计 计算角度偏差
	
	//步骤三，计算卡尔曼增益
	//公式：Kg(k)= P(k|k-1)H^T/(HP(k|k-1)H^T+R)
	//Kg = (K_0,K_1) 对应Angle,Q_bias增益
	//H = (1,0)	可由z=HX+v求出z:Accel
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	E = R_angle + C_0 * PCt_0;
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	//步骤四，后验估计误差协方差
	//公式：P(k|k)=(I-Kg(k)H)P(k|k-1)
	//也可写为：P(k|k)=P(k|k-1)-Kg(k)HP(k|k-1)
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];
	PP[0][0] -= K_0 * t_0;		
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
	
	//步骤五，计算最优角速度值
	//公式：X(k|k)= X(k|k-1)+Kg(k)(Z(k)-X(k|k-1))
	Angle_X_Final += K_0 * Angle_err;	 //后验估计，给出最优估计值
	Q_bias        += K_1 * Angle_err;	 //后验估计，跟新最优估计值偏差
	Gyro_x         = Gyro - Q_bias;	 
}

void Kalman_Filter_Y(float Accel,float Gyro) 		
{
	Angle_Y_Final += (Gyro - Q_bias) * dt;
	P[0]=Q_angle - PP[0][1] - PP[1][0]; 
	P[1]=-PP[1][1];
	P[2]=-PP[1][1];
	P[3]=Q_gyro;	
	PP[0][0] += P[0] * dt; 
	PP[0][1] += P[1] * dt;  
	PP[1][0] += P[2] * dt;
	PP[1][1] += P[3] * dt;	
	Angle_err = Accel - Angle_Y_Final;		
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];	
	E = R_angle + C_0 * PCt_0;	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];
	PP[0][0] -= K_0 * t_0;		
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;		
	Angle_Y_Final	+= K_0 * Angle_err;
	Q_bias	+= K_1 * Angle_err;	 
	Gyro_y   = Gyro - Q_bias;	 
}
void Kalman_Filter_Z(float Accel,float Gyro) 		
{
	Angle_Z_Final += (Gyro - Q_bias) * dt;
	P[0]=Q_angle - PP[0][1] - PP[1][0]; 
	P[1]=-PP[1][1];
	P[2]=-PP[1][1];
	P[3]=Q_gyro;	
	PP[0][0] += P[0] * dt; 
	PP[0][1] += P[1] * dt;  
	PP[1][0] += P[2] * dt;
	PP[1][1] += P[3] * dt;	
	Angle_err = Accel - Angle_Z_Final;		
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];	
	E = R_angle + C_0 * PCt_0;	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];
	PP[0][0] -= K_0 * t_0;		
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;		
	Angle_Z_Final	+= K_0 * Angle_err;
	Q_bias+= K_1 * Angle_err;	 
	Gyro_z   = Gyro - Q_bias;	 
}