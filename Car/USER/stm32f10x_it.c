/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "delay.h"
#include "key.h"
#include "MotorDrive.h"
#include "ultrasound.h"

unsigned int UltraDis = 900;
u8 overcount = 0;
u8 Have_OB = 0;

extern u8 StatusMode;
extern u8 Stat;

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

void EXTI2_IRQHandler(void)
{ 
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		delay_init();
		{ 
			StatusMode++;			//have problem not solved
			delay_ms(10);
			if(StatusMode%3 == 0)
				Stat = Single_Track;
			else if(StatusMode%3 == 1)
				Stat = Double_Track;
			else if(StatusMode%3 == 2)
				Stat = Maze;
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI1_IRQHandler(void)
{ 
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{
		overcount = 0;
		TIM_SetCounter(TIM1, 0);
		TIM_Cmd(TIM1, ENABLE);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == SET);
		TIM_Cmd(TIM1, DISABLE);
		
		if(TIM_GetCounter(TIM1) > UltraDis){
			Have_OB = 0;
		}else{
			Have_OB = 1;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void TIM1_IRQHandler(void)
{
if(TIM_GetITStatus(TIM1, TIM_IT_Update)!=RESET)
  {
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		overcount++;
  }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
