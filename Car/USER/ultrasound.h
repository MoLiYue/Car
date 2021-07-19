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
// 超声波避障
//-----------------------------------------------------------------
#define		Ul_Not_Find_Barrier			0x00	// 未发现障碍
#define		Ul_Find_Barrier			    0x01	// 发现障碍

#define     Tracking_Mode               0x00    //循迹模式
#define     Obstacle_Avoidance_Mode     0x01    //避障模式

#define     Too_Far1                     0x00    //距离过远
#define     Too_Far0                     0x01    //距离过远
#define     Middle                       0x02    //距离适中
#define     Too_Near0                    0x03    //距离过远
#define     Too_Near1                    0x04    //距离过远
//-----------------------------------------------------------------

#define ANGLE0	(250)       //右
#define ANGLE1	(500)
#define ANGLE2	(750)       //前
#define ANGLE3	(1000)
#define ANGLE4	(1250)      //左

void Ultrasound_Init(void);

#endif