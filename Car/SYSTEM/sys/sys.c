#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ZYSTM32-A0���������ذ�
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й����ʺ�STM32F10xϵ�У�
//����delay_us,delay_ms
//�������
//www.hnzhiyu.cn
//��������:2017/4/14
//�汾��V1.8
//All rights reserved
//********************************************************************************
//////////////////////////////////////////////////////////////////////////////////  
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
//void WFI_SET(void)
//{
//	__ASM volatile("wfi");		  
//}
////�ر������ж�
//void INTX_DISABLE(void)
//{		  
//	__ASM volatile("cpsid i");
//}
////���������ж�
//void INTX_ENABLE(void)
//{
//	__ASM volatile("cpsie i");		  
//}
////����ջ����ַ
////addr:ջ����ַ
//__asm void MSR_MSP(u32 addr) 
//{
//    MSR MSP, r0 			//set Main Stack value
//    BX r14
//}

void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}