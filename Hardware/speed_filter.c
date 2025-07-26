#include "speed_filter.h"


#define SPEED_FILTER_LEN 5

// �������˲�����������
static float speed_buffer_left[SPEED_FILTER_LEN] = {0};
static float speed_buffer_right[SPEED_FILTER_LEN] = {0};
static uint8_t speed_index_left = 0;
static uint8_t speed_index_right = 0;

// �����˲����
static float filtered_speed_left = 0;
static float filtered_speed_right = 0;

/**
 * @brief �����ٶȻ���ƽ���˲�
 * @param new_speed �������ٶȣ���λ��m/s��
 * @return �˲���������ٶȣ���λ��m/s��
 */
float speed_filter_left(float new_speed)
{
    speed_buffer_left[speed_index_left] = new_speed;
    speed_index_left = (speed_index_left + 1) % SPEED_FILTER_LEN;

    float sum = 0;
    for (int i = 0; i < SPEED_FILTER_LEN; i++) {
        sum += speed_buffer_left[i];
    }
    filtered_speed_left = sum / SPEED_FILTER_LEN;
    return filtered_speed_left;
}

/**
 * @brief �����ٶȻ���ƽ���˲�
 * @param new_speed �������ٶȣ���λ��m/s��
 * @return �˲���������ٶȣ���λ��m/s��
 */
float speed_filter_right(float new_speed)
{
    speed_buffer_right[speed_index_right] = new_speed;
    speed_index_right = (speed_index_right + 1) % SPEED_FILTER_LEN;

    float sum = 0;
    for (int i = 0; i < SPEED_FILTER_LEN; i++) {
        sum += speed_buffer_right[i];
    }
    filtered_speed_right = sum / SPEED_FILTER_LEN;
    return filtered_speed_right;
}

/**
 * @brief ��ȡ��ǰ�˲���������ٶȣ�m/s��
 */
float get_filtered_speed_left(void)
{
    return filtered_speed_left;
}

/**
 * @brief ��ȡ��ǰ�˲���������ٶȣ�m/s��
 */
float get_filtered_speed_right(void)
{
    return filtered_speed_right;
}
