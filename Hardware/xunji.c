#include "stm32f10x.h"                  // STM32��׼��ͷ�ļ�
#include "xunji.h"


extern int red_sensors[8];            // �ⲿ�������⴫����״̬����
int  Trackn = 0;                      // ���������״̬������ʾ

int red_sensors[8] = {0};             // �������ϴ�״̬����
int comePointFlag = 0;                // ������״̬�仯��־�������ػ��½��ؼ�⣩

/**
 * @brief �޷���������ֵ֤��[min, max]��Χ��
 * @param value ����ֵ
 * @param min ��Сֵ
 * @param max ���ֵ
 * @return �޷����ֵ
 */
int constrain(int value, int min, int max) 
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * @brief ѭ��������GPIO��ʼ��
 * ����8·GPIO���룬��������ģʽ
 */
void Xunji_Init(void)
{
	/*����GPIOA��GPIOB��GPIOCʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/*GPIO��ʼ������ - ��������*/
	GPIO_InitTypeDef GPIO_InitStructure;

	// GPIOA��11��15��0������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           // ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_15|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // �ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// GPIOB��4��5������
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure1);

	// GPIOC��13��14��15������
	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure2);
}

/**
 * @brief ��ȡ8·ѭ��������״̬�����´���������
 * @param read_senors �����8λ����ָ�룬���ڴ洢��ȡ��״̬��0��1��
 */
void read_sensors(int*read_senors)
{
	read_senors[0]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15);
	read_senors[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	read_senors[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);
	read_senors[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
	read_senors[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	read_senors[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
	read_senors[6]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
	read_senors[7]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14);

	// ��8��������״̬��λ��ϳ�һ������������״̬�жϺ���ʾ
	Trackn = read_senors[0] * 128 +read_senors[1]*64+ read_senors[2]*32 + 
		read_senors[3]*16+read_senors[4]*8+ read_senors[5]*4+ 
		read_senors[6]*2+ read_senors[7]*1;
}

// GPIO�˿ں�����ӳ�����飬����ѭ����ȡ
GPIO_TypeDef* Xunji_PIN_PORTS[8] = { GPIOC, GPIOA,GPIOA, GPIOA,GPIOB, GPIOB,GPIOC, GPIOC};
uint16_t Xunji_PIN_PINS[8] = {GPIO_Pin_15, GPIO_Pin_0, GPIO_Pin_11, GPIO_Pin_15,GPIO_Pin_5, GPIO_Pin_4, GPIO_Pin_13, GPIO_Pin_14};

/**
 * @brief ���º��⴫����״̬�������ر仯
 * 
 * ���ݵ�ǰ�ɼ��Ĵ�����״̬��֮ǰ״̬�Ƚϣ���⴫����״̬�Ƿ����������ػ��½��أ�
 * ������ȫ�ֱ���comePointFlag��־��
 */
void update_redSensor(void) 
{
    int sensors[8];  // ��ʱ���鱣�浱ǰ������״̬

    // �����ȡGPIO����״̬��ע�⴫������������ǵ͵�ƽ��Ч��ת��Ϊ0/1
    for (int i = 0; i < 8; i++)
    {
        // GPIO_ReadInputDataBit����1��ʾ�ߵ�ƽ�����������ܵ͵�ƽ��Ч
        // ������������� ?: ת��Ϊ 0/1״̬
        sensors[i] = GPIO_ReadInputDataBit(Xunji_PIN_PORTS[i], Xunji_PIN_PINS[i]) ? 0 : 1;
    }

    // �Ƚϵ�ǰ���ϴ�״̬��������
    for (int i = 0; i < 8; i++) 
	{
        if (sensors[i] == 0 && red_sensors[i] == 1) 
		{
            comePointFlag = 1; // �����ؼ�⵽����ʾ��1��0
        } 
		else if (sensors[i] == 1 && red_sensors[i] == 0) 
		{
            comePointFlag = -1; // �½��ؼ�⵽����ʾ��0��1
        }
        red_sensors[i] = sensors[i]; // ���»���״̬
    }
}


/**
 * @brief С��ѭ�������ƺ���
 * @param Motor_leftSetSpeed �����ٶ�ָ�루�������贫��ַ��
 * @param Motor_rightSetSpeed �ҵ���ٶ�ָ�루�������贫��ַ��
 * @param base_v �����ٶȣ����������PWM��׼�ٶȣ�
 * @note ����ʹ��PID���ڵ���ٶ�ʵ��ѭ��
 */
void trait(int* Motor_leftSetSpeed, int* Motor_rightSetSpeed, int base_v) 
{
    static float last_error = 0;    // ��һ��������΢�ּ���
    static float integral = 0;      // �����ۼ��������ڻ��ּ���
		
    // ����ѭ������Ȩ��� 7��5��3��1
    float error = (red_sensors[7] - red_sensors[0]) * 7 + 
                  (red_sensors[6] - red_sensors[1]) * 5 +
                  (red_sensors[5] - red_sensors[2]) * 3 + 
                  (red_sensors[4] - red_sensors[3]) * 1;
    
    //PID ��������
    float Kp = 0.8;  // ����ϵ��
    float Ki = 0.01; // ����ϵ��
    float Kd = 0.3;  // ΢��ϵ��
    
    // PID�����㷨
    integral += error;                        // �����ۼ�
    float derivative = error - last_error;  // ���΢��
    float correction = Kp * error + Ki * integral + Kd * derivative; // PID���
    last_error = error;                      // �����ϴ����
    
    // �������ҵ�������ٶȣ����޷���
    *Motor_leftSetSpeed = constrain(base_v + correction, -100, 100);
    *Motor_rightSetSpeed = constrain(base_v - correction, -100, 100);
}
