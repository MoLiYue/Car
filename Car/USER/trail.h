#ifndef	__TRAIL_H
#define __TRAIL_H

#include "stm32f10x.h"


// S_Trail_Input�ĵ���λ�ֱ��Ӧ[PB5��PB4��PB3]��״ֵ̬
// δ��������(���յ������)����Ӧ״̬ = 0
// ��������(δ���յ������)����Ӧ״̬ = 1
//-----------------------------------------------------

// ����Ѱ�����
//---------------------------------------------------------------------
#define		Not_Find_Black_Line				0x00	// δ���ֺ���

#define		Left_Find_Black_Line			0x02	// ��෢�ֺ���

#define		Right_Find_Black_Line			0x01	// �Ҳ෢�ֺ���

#define		All_Find_Black_Line				0x03	// ȫ�����ֺ���
//---------------------------------------------------------------------

void Trail_Input_Init_JX(void);		// ����Ѱ����ʼ��

u8 Trail_black_line(void);		// ����Ѱ������


#endif	/* __TRAIL_H*/

