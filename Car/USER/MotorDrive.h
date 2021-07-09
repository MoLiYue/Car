#ifndef __MOTORDRIVE_H
#define __MOTORDRIVE_H


#include "stm32f10x.h"
#include "bit_band.h"

// 小车的熄火/刹车宏定义
//-----------------------------------
#define CAR_FLAMEOUT	(0)	// 熄火

#define CAR_BREAK		(1)	// 刹车

extern u8 DIFFERENTIAL;
//-----------------------------------

// PB7模式配置
//----------------------------------------------------------------------------
// PB7：通用推挽输出
#define PB7_Out_PP  { GPIOB->CRL&=0X0FFFFFFF; GPIOB->CRL|=(u32)0x03<<(7*4); }

// PB7：复用推挽输出
#define PB7_AF_PP   { GPIOB->CRL&=0X0FFFFFFF; GPIOB->CRL|=(u32)0x09<<(7*4); }
//----------------------------------------------------------------------------

// PB8模式配置
//----------------------------------------------------------------------------
// PB8：通用推挽输出
#define PB8_Out_PP  { GPIOB->CRH&=0XFFFFFFF0; GPIOB->CRH|=(u32)0x03<<(0*4); }

// PB8：复用推挽输出
#define PB8_AF_PP   { GPIOB->CRH&=0XFFFFFFF0; GPIOB->CRH|=(u32)0x09<<(0*4); }
//----------------------------------------------------------------------------

// PB9模式配置
//----------------------------------------------------------------------------
// PB9：通用推挽输出
#define PB9_Out_PP  { GPIOB->CRH&=0XFFFFFF0F; GPIOB->CRH|=(u32)0x03<<(1*4); }

// PB9：复用推挽输出
#define PB9_AF_PP   { GPIOB->CRH&=0XFFFFFF0F; GPIOB->CRH|=(u32)0x09<<(1*4); }
//----------------------------------------------------------------------------

// PA4模式配置
//----------------------------------------------------------------------------
// PA4：通用推挽输出
#define PA4_Out_PP  { GPIOA->CRL&=0XFFFF0FFF; GPIOA->CRL|=(u32)0x03<<(4*4); }

// PA4：复用推挽输出
#define PA4_AF_PP   { GPIOA->CRL&=0XFFFF0FFF; GPIOA->CRL|=(u32)0x09<<(4*4); }
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void Motor_LF_forward(u8 speed);		// 左前轮=前转(速度 = speed%)
void Motor_LF_backward(u8 speed);		// 左前轮=后转(速度 = 1-speed%)
void Motor_LF_Stop(u8 Wheel_STOP);		// 左前轮=停止(熄火/刹车)

void Motor_RF_forward(u8 speed);		// 右前轮=前转(速度 = speed%)
void Motor_RF_backward(u8 speed);		// 右前轮=后转(速度 = 1-speed%)
void Motor_RF_Stop(u8 Wheel_STOP);		// 右前轮=停止(熄火/刹车)

void Car_Stop(u8 Wheel_STOP);			// 小车=停止(熄火/刹车)
void Car_forward(u8 speed);				// 小车向前(速度 = speed%)
void Car_backward(u8 speed);			// 小车向后(速度 = -speed%)

void Car_Turn_Left(u8 speed);			// 小车左转(速度 = speed%)
void Car_Turn_Right(u8 speed);			// 小车右转(速度 = speed%)

void Car_Become_Right(u8 speed);
void Car_Become_Left(u8 speed);

void Car_Become_Right_Back(u8 speed);
void Car_Become_Left_Back(u8 speed);
//----------------------------------------------------------------------------


#endif /* __MOTORDRIVE_H */