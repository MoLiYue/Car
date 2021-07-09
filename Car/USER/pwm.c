#include "pwm.h"
#include "MotorDrive.h"

void TIM4_PWM_Init_JX(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
	 /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	 
	 
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = TIM4_Reload_Num;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM4_Frequency_Divide;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);


	/* PWM1 Mode configuration: Channel 3,4 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	//CCR3 left wheel				(backward speed = 100 - CCR3_Val)
	//CCR4 right wheel				(backward speed = 100 - CCR4_Val)
	PA4_Out_PP;
	PA_out(4) = 0;
	PB7_Out_PP;
	PB_out(7) = 0;
	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

  //TIM_ARRPreloadConfig(TIM4, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM4, ENABLE);
}