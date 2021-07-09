#include "trail.h"


// ����Ѱ����ʼ��(����ʼ��Ϊ��������)
// Trail -- PB0
// Trai2 -- PA7

//----------------------------------------------------------------------------------------------
void Trail_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// ʹ��GPIOB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);			// GPIOBʱ��ʹ��
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			// ����ʱ��ʹ��

	
	// Ѱ����Trail--PB0�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	// Trail--PB0	LC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// ��������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// ����ģʽ����Ҫ��˿��ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);							// ��ʼ��PB0
	
	// Ѱ����Trail--PA7�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	// Trail--PA7	RC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// ��������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// ����ģʽ����Ҫ��˿��ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);							// ��ʼ��PA7
	
}
//----------------------------------------------------------------------------------------------


// ����Ѱ������
// S_Trail_Input�ĵ���λ�ֱ��Ӧ[PB0\PA7]��״ֵ̬
// δ��������(���յ������)����Ӧ״̬ = 0
// ��������(δ���յ������)����Ӧ״̬ = 1
//----------------------------------------------------
u8 Trail_black_line(void)
{
	u8 S_Trail_Input = 0 ;
	
	S_Trail_Input = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)<<1;
	return S_Trail_Input = S_Trail_Input + GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
	
}
//----------------------------------------------------

