#ifndef __ULTRASOUND_H
#define __ULTRASOUND_H

#include "stm32f10x.h"

// 溢出时间：100us
//--------------------------------
// 分频系数：720（分频值+1）
// 计数频率：100kHz
// 计数周期：10us
// 重装载值：99
// 溢出周期：1ms
// 溢出频率：1kHz
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