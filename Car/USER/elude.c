#include "elude.h"
#include "delay.h"
#include "MotorDrive.h"

//u8 S_Elude_Input = 0 ;		// 红外避障模块的返回值


// 红外避障初始化(将PB1初始化为上拉输入)

//----------------------------------------------------------------------------------------------
void Elude_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);			// GPIOB时钟使能
	
	
	// 避障：Elude--PB1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	// Elude--PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// 上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// 输入模式不需要设端口速度
	GPIO_Init(GPIOB, &GPIO_InitStructure);							// 初始化PB1
	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	
//	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
}
//----------------------------------------------------------------------------------------------


// 红外避障检测函数
// S_Elude_Input对应[PB1]的状态值
// 未遇到障碍(未接收到红外光)：对应状态 = 1
// 遇到障碍(接收到红外光)：对应状态 = 0
//-------------------------------------------------------------
u8 Elude_detect_barrier(void)
{
	u8 S_Elude_Input = 0 ;
	
	return S_Elude_Input = (((u8)GPIOB->IDR) & 0x02)>>1;
}
//-------------------------------------------------------------


