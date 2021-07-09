#include "key.h"

u8 StatusMode = 0;

	
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	// Elude--PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;
	if(mode)
		key_up=1;
	if(key_up&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)))
	{ 
		delay_ms(10);
		key_up=0;
		if(StatusMode%3 == 0)
			return Single_Track;
		else if(StatusMode%3 == 1)
			return Double_Track;
		else if(StatusMode%3 == 2)
			return Maze;
		StatusMode++;
	}
	else if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
		key_up=1;
	return 0;
}
