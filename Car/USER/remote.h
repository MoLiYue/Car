#ifndef __REMOTE_H
#define __REMOTE_H


#include "stm32f10x.h"

//--------------------------------------------------------------
#define	TIM2_Frequency_Divide	(71)		// TIM1时钟预分频值
#define	TIM2_Reload_Num			(9999)		// 自动重装载寄存器的值
//--------------------------------------------------------------
extern u8 RmtSta;
extern u16 Dval;
extern u32 RmtRec;
extern u8 RmtCnt;

#endif /* __REMOTE_H */