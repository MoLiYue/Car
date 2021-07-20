#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#include "delay.h"

#define MODENUM (5)

#define Single_Track	(0x00)
#define Double_Track	(0x01)
#define Maze_V1			(0x02)
#define Maze_V2			(0x03)
#define RemoteControl   (0x04)

extern u8 StatusMode;

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
void EXTI2_IRQHandler(void);

#endif