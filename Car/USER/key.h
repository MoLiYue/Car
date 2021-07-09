#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#include "delay.h"


#define Single_Track	(0x00)
#define Double_Track	(0x01)
#define Maze					(0x02)

extern u8 StatusMode;

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
void EXTI2_IRQHandler(void);

#endif