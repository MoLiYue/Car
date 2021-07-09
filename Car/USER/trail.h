#ifndef	__TRAIL_H
#define __TRAIL_H

#include "stm32f10x.h"


// S_Trail_Input的低三位分别对应[PB5、PB4、PB3]的状态值
// 未碰到黑线(接收到红外光)：对应状态 = 0
// 碰到黑线(未接收到红外光)：对应状态 = 1
//-----------------------------------------------------

// 黑线寻迹情况
//---------------------------------------------------------------------
#define		Not_Find_Black_Line				0x00	// 未发现黑线

#define		Left_Find_Black_Line			0x02	// 左侧发现黑线

#define		Right_Find_Black_Line			0x01	// 右侧发现黑线

#define		All_Find_Black_Line				0x03	// 全部发现黑线
//---------------------------------------------------------------------

void Trail_Input_Init_JX(void);		// 红外寻迹初始化

u8 Trail_black_line(void);		// 黑线寻迹函数


#endif	/* __TRAIL_H*/

