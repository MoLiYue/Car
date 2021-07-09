#include "bit_band.h"
#include "stm32f10x.h"
#include "Motordrive.h"
#include "pwm.h"
#include "elude.h"
#include "trail.h"
#include "sys.h"
#include "delay.h"
#include "key.h"
#include "ultrasound.h"

//    GPIOB->BRR |= (1<<7);	//PB7 Set 1	(backward)	Set 0 (forward)							&= ~(1<<8);
//    
//    GPIOB->BSRR  |= (1<<8);	//PB9 Set 1 
//		
//		GPIOA->BRR |= (1<<4);	//PA4 Set 1  (backward)    Set 0 (forward)
//		
//		GPIOB->BRR  |= (1<<9);	//PB9 Set 0

u8 Stat = 0;
extern u8 Have_OB;
extern unsigned int UltraDis;

void Maze_Track(u8 S_Trail_Input);
void Single_Line(u8 S_Trail_Input, u8 S_Elude_Input, u8 Forward_Speed, u8 TurnSpeed, u8 Differential);
void Dubble_Line(u8 S_Trail_Input, u8 S_Elude_Input);

void Single_Line(u8 S_Trail_Input, u8 S_Elude_Input, 
									u8 Forward_Speed, u8 TurnSpeed, u8 Differential){
	DIFFERENTIAL = Differential;
	//S_Elude_Input = Elude_detect_barrier();	// 红外避障检测

	// 未发现障碍
	//-------------------------------------------------------	
	if( S_Elude_Input == Not_Find_Barrier )	{									
		S_Trail_Input = Trail_black_line();		// 黑线检测函数
		// 未发现黑线    forward
		//-------------------------------------------------------	
		if(S_Trail_Input == Not_Find_Black_Line)	{
			Car_forward(Forward_Speed);				// 前进
		}
		//-------------------------------------------------------

		// 左侧发现黑线
		//----------------------------------------------
		else if(S_Trail_Input == Left_Find_Black_Line){
			//Car_Stop(CAR_BREAK);
			Car_Become_Left(TurnSpeed);	// 左转
			//delay_ms(100);
		}
	
		// 右侧发现黑线
		//----------------------------------------------
		else if(S_Trail_Input == Right_Find_Black_Line){
			//Car_Stop(CAR_BREAK);
			Car_Become_Right(TurnSpeed);	// 右转
			//delay_ms(100);
		}
	
		// 其他情况
		//----------------------------------------------
		else {
			Car_Stop(CAR_FLAMEOUT);	// 熄火
		}
	//----------------------------------------------
	// Single Line
	}
	// 发现障碍
	//----------------------------------------------
	else{
		Car_backward(50);	// 后退
		delay_ms(500);
		Car_Turn_Left(50);	// 左转
		delay_ms(500);
	}
}

void Dubble_Line(u8 S_Trail_Input, u8 S_Elude_Input){
	//S_Elude_Input = Elude_detect_barrier();	// 红外避障检测

	// 未发现障碍
	//-------------------------------------------------------	
	if( S_Elude_Input == Not_Find_Barrier )	{
		S_Trail_Input = Trail_black_line();		// 黑线检测函数-
		// 未发现黑线    forward
		//-------------------------------------------------------	
		if(S_Trail_Input == Not_Find_Black_Line)	{
			Car_forward(40);				// 前进
		}
		//-------------------------------------------------------

		// 左侧发现黑线
		//----------------------------------------------
		else if(S_Trail_Input == Left_Find_Black_Line){
			//Car_backward(50);
			//delay_ms(300);
			Car_Turn_Right(50);
			delay_ms(150);
		}

		// 右侧发现黑线
		//----------------------------------------------
		else if(S_Trail_Input == Right_Find_Black_Line){
			//Car_backward(50);
			//delay_ms(300);
			Car_Turn_Left(50);
			delay_ms(150);
		}
		// 其他情况
		//----------------------------------------------
		else {
//			Car_backward(50);	// 后退
//			delay_ms(500);
//			Car_Turn_Left(50);	//Left
//			delay_ms(200);
			
			Car_Stop(CAR_BREAK);
			//delay_ms(300);
		}
	//----------------------------------------------
	// Dubble Line
	}else{
		Car_backward(50);	// 后退
		delay_ms(500);
		Car_Turn_Left(50);	// 左转
		delay_ms(500);
	}
}

void Maze_Track(u8 S_Trail_Input){
	
	UltraDis = 700;
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	delay_us(10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	delay_ms(60);

	if(Have_OB == 0){
		//Car_forward(40);
		
		Single_Line(S_Trail_Input, Elude_detect_barrier(), 40, 40, 40);
	}else{
		Car_Stop(CAR_BREAK);

		TIM_SetCompare1(TIM5,ANGLE4);//Left
		Have_OB = 0;
		delay_ms(1000);								//wait for DUOJI
		
		UltraDis = 900;
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		delay_us(10);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		delay_ms(60);


		if(Have_OB == 0){
			//Car_backward(50);	// 后退
			//delay_ms(500);
			Car_Turn_Left(50);	//Left
			delay_ms(370);
			Car_Stop(CAR_BREAK);
			
			TIM_SetCompare1(TIM5,ANGLE2);//Forward
			Have_OB = 0;
		}else{
		
			TIM_SetCompare1(TIM5,ANGLE0);//Right
			Have_OB = 0;
			delay_ms(1000);								//wait for DUOJI
		
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			delay_us(10);
			GPIO_ResetBits(GPIOC,GPIO_Pin_0);
			delay_ms(60);
			
			if(Have_OB == 0){
				//Car_backward(50);	// 后退
				//delay_ms(500);
				Car_Turn_Right(50);	// Right
				delay_ms(370);
				Car_Stop(CAR_BREAK);
				
				TIM_SetCompare1(TIM5,ANGLE2);//Forward
				Have_OB = 0;
			}else{
				Car_Turn_Right(50);	// Turn Around
				delay_ms(700);
				//Car_forward(40);
				Car_Stop(CAR_BREAK);
				
				TIM_SetCompare1(TIM5,ANGLE2);//Forward
				Have_OB = 0;
			}
		}
		delay_ms(1000);								//wait for DUOJI
	}
}

int main(void){
	
	
	
	delay_init();
	NVIC_Configuration();
	Elude_Input_Init_JX();	//hongwai
	TIM4_PWM_Init_JX();
	Trail_Input_Init_JX();
	KEY_Init();
	Ultrasound_Init();
	
while(1){
	
	u8 S_Elude_Input = 0;
	u8 S_Trail_Input = 0;
	
	switch (Stat){
		
		case Single_Track:
			Single_Line(S_Trail_Input, Elude_detect_barrier(), 50, 80, 90);
			break;
				
		case Double_Track:
			Dubble_Line(S_Trail_Input, Elude_detect_barrier());
			break;
			
		case Maze:
			Maze_Track(S_Trail_Input);
			break;
		
		default:
			break;
		}
	}
}

