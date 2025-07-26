#ifndef __SPEED_FILTER_H
#define __SPEED_FILTER_H

#include "stdint.h"

/* �˲����� */
#define SPEED_FILTER_LEN 5

/* �����ٶȻ���ƽ���˲�
 * @param new_speed �������ٶȣ���λ��m/s��
 * @return �˲���������ٶȣ���λ��m/s��
 */
float speed_filter_left(float new_speed);

/* �����ٶȻ���ƽ���˲�
 * @param new_speed �������ٶȣ���λ��m/s��
 * @return �˲���������ٶȣ���λ��m/s��
 */
float speed_filter_right(float new_speed);

/* ��ȡ��ǰ�˲���������ٶȣ���λ��m/s�� */
float get_filtered_speed_left(void);

/* ��ȡ��ǰ�˲���������ٶȣ���λ��m/s�� */
float get_filtered_speed_right(void);

#endif /* __SPEED_FILTER_H */