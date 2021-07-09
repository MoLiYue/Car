#ifndef __MOTORDRIVE_H
#define __MOTORDRIVE_H


#include "stm32f10x.h"
#include "bit_band.h"

// С����Ϩ��/ɲ���궨��
//-----------------------------------
#define CAR_FLAMEOUT	(0)	// Ϩ��

#define CAR_BREAK		(1)	// ɲ��

extern u8 DIFFERENTIAL;
//-----------------------------------

// PB7ģʽ����
//----------------------------------------------------------------------------
// PB7��ͨ���������
#define PB7_Out_PP  { GPIOB->CRL&=0X0FFFFFFF; GPIOB->CRL|=(u32)0x03<<(7*4); }

// PB7�������������
#define PB7_AF_PP   { GPIOB->CRL&=0X0FFFFFFF; GPIOB->CRL|=(u32)0x09<<(7*4); }
//----------------------------------------------------------------------------

// PB8ģʽ����
//----------------------------------------------------------------------------
// PB8��ͨ���������
#define PB8_Out_PP  { GPIOB->CRH&=0XFFFFFFF0; GPIOB->CRH|=(u32)0x03<<(0*4); }

// PB8�������������
#define PB8_AF_PP   { GPIOB->CRH&=0XFFFFFFF0; GPIOB->CRH|=(u32)0x09<<(0*4); }
//----------------------------------------------------------------------------

// PB9ģʽ����
//----------------------------------------------------------------------------
// PB9��ͨ���������
#define PB9_Out_PP  { GPIOB->CRH&=0XFFFFFF0F; GPIOB->CRH|=(u32)0x03<<(1*4); }

// PB9�������������
#define PB9_AF_PP   { GPIOB->CRH&=0XFFFFFF0F; GPIOB->CRH|=(u32)0x09<<(1*4); }
//----------------------------------------------------------------------------

// PA4ģʽ����
//----------------------------------------------------------------------------
// PA4��ͨ���������
#define PA4_Out_PP  { GPIOA->CRL&=0XFFFF0FFF; GPIOA->CRL|=(u32)0x03<<(4*4); }

// PA4�������������
#define PA4_AF_PP   { GPIOA->CRL&=0XFFFF0FFF; GPIOA->CRL|=(u32)0x09<<(4*4); }
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void Motor_LF_forward(u8 speed);		// ��ǰ��=ǰת(�ٶ� = speed%)
void Motor_LF_backward(u8 speed);		// ��ǰ��=��ת(�ٶ� = 1-speed%)
void Motor_LF_Stop(u8 Wheel_STOP);		// ��ǰ��=ֹͣ(Ϩ��/ɲ��)

void Motor_RF_forward(u8 speed);		// ��ǰ��=ǰת(�ٶ� = speed%)
void Motor_RF_backward(u8 speed);		// ��ǰ��=��ת(�ٶ� = 1-speed%)
void Motor_RF_Stop(u8 Wheel_STOP);		// ��ǰ��=ֹͣ(Ϩ��/ɲ��)

void Car_Stop(u8 Wheel_STOP);			// С��=ֹͣ(Ϩ��/ɲ��)
void Car_forward(u8 speed);				// С����ǰ(�ٶ� = speed%)
void Car_backward(u8 speed);			// С�����(�ٶ� = -speed%)

void Car_Turn_Left(u8 speed);			// С����ת(�ٶ� = speed%)
void Car_Turn_Right(u8 speed);			// С����ת(�ٶ� = speed%)

void Car_Become_Right(u8 speed);
void Car_Become_Left(u8 speed);

void Car_Become_Right_Back(u8 speed);
void Car_Become_Left_Back(u8 speed);
//----------------------------------------------------------------------------


#endif /* __MOTORDRIVE_H */