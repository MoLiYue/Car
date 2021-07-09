#ifndef __ULTRASOUND_H
#define __ULTRASOUND_H

#include "stm32f10x.h"

// ���ʱ�䣺100us
//--------------------------------
// ��Ƶϵ����720����Ƶֵ+1��
// ����Ƶ�ʣ�100kHz
// �������ڣ�10us
// ��װ��ֵ��99
// ������ڣ�1ms
// ���Ƶ�ʣ�1kHz
//--------------------------------------------------------------

#define TIM5_Reload_Num (9999)
#define TIM5_Frequency_Divide	(143)

#define TIM1_Reload_Num (49999)
#define TIM1_Frequency_Divide	(71)

#define ANGLE0	(250)
#define ANGLE1	(500)
#define ANGLE2	(750)
#define ANGLE3	(1000)
#define ANGLE4	(1250)

void Ultrasound_Init(void);

#endif