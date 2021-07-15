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

extern u8 RmtSta;
extern u16 Dval;
extern u32 RmtRec;
extern u8 RmtCnt;

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
      delay_ms(10);
      if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)){
			StatusMode++;			//have problem not solved
			if(StatusMode%4 == 0)
				Stat = Single_Track;
			else if(StatusMode%4 == 1)
				Stat = Double_Track;
			else if(StatusMode%4 == 2)
				Stat = Maze;
      else if(StatusMode%4 == 3)
				Stat = RemoteControl;
      }
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

void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET)
  {
		if(RmtSta&0x80){ // 上次有数据被接收到了
      RmtSta&=~0X10; // 取消上升沿已经被捕获标记
      if((RmtSta&0X0F)==0X00)
        RmtSta |= 1<<6;// 标记已经完成一次键值信息采集
      if((RmtSta &0X0F)<14)
        RmtSta++;
      else{ 
        RmtSta&=~(1<<7);// 清空引导标识
        RmtSta&=0XF0; // 清空计数器
      } 
    }
  }
  if(TIM_GetITStatus(TIM2, TIM_IT_CC2)!=RESET){
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) { //上升沿捕获
      TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling); //下降沿捕获
      TIM_SetCounter(TIM2,0); // 清空定时器值
      RmtSta |= 0X10; // 标记上升沿已经被捕获
    }else { //下降沿捕获
      Dval = TIM_GetCapture2(TIM2);// 读取 CCR1 也可以清 CC1IF 标志位 
      TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); // 上升沿捕获
      if(RmtSta&0X10) { // 完成一次高电平捕获
        if(RmtSta&0X80)// 接收到了引导码
        { 
          if(Dval > 300 && Dval < 800) //560 为标准值 ,560us
          { 
            RmtRec <<= 1; // 左移一位
            RmtRec |= 0; // 接收到 0 
          }else if(Dval > 1400 && Dval < 1800) //1680 为标准值 ,1680us
          { 
            RmtRec <<= 1; // 左移一位
            RmtRec |= 1; // 接收到 1 
          }else if(Dval > 2200 && Dval < 2600)  // 得到按键键值增加的信息
                                          //2500 为标准值 2.5ms
          {
            RmtCnt++; // 按键次数增加 1次 
            RmtSta &= 0XF0; // 清空计时器
          }
        }else if(Dval > 4200 && Dval < 4700)  //4500 为标准值 4.5ms
        {
          RmtSta |= 1<<7; // 标记成功接收到了引导码
          RmtCnt = 0; // 清除按键次数计数器
        }
      }
      RmtSta &= ~(1<<4);
    }
  }
  TIM_ClearFlag(TIM2,TIM_IT_Update|TIM_IT_CC2);
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
