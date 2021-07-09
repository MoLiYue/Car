#include "trail.h"


// 红外寻迹初始化(将初始化为上拉输入)
// Trail -- PB0
// Trai2 -- PA7

//----------------------------------------------------------------------------------------------
void Trail_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// 使能GPIOB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);			// GPIOB时钟使能
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			// 复用时钟使能

	
	// 寻迹：Trail--PB0端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	// Trail--PB0	LC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// 上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// 输入模式不需要设端口速度
	GPIO_Init(GPIOB, &GPIO_InitStructure);							// 初始化PB0
	
	// 寻迹：Trail--PA7端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	// Trail--PA7	RC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// 上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// 输入模式不需要设端口速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);							// 初始化PA7
	
}
//----------------------------------------------------------------------------------------------


// 黑线寻迹函数
// S_Trail_Input的低三位分别对应[PB0\PA7]的状态值
// 未碰到黑线(接收到红外光)：对应状态 = 0
// 碰到黑线(未接收到红外光)：对应状态 = 1
//----------------------------------------------------
u8 Trail_black_line(void)
{
	u8 S_Trail_Input = 0 ;
	
	S_Trail_Input = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)<<1;
	return S_Trail_Input = S_Trail_Input + GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
	
}
//----------------------------------------------------

