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
#include "remote.h"

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
extern u8 Maze_Mode;

void Maze_Track(u8 S_Trail_Input);
void Single_Line(u8 S_Trail_Input, u8 S_Elude_Input, u8 Forward_Speed, u8 TurnSpeed, u8 Differential);
void Dubble_Line(u8 S_Trail_Input, u8 S_Elude_Input);
void Maze_Track(u8 S_Trail_Input);
void Maze_Track_v2(u8 S_Trail_Input);
void Send_UltraSound_Signal();


void Send_UltraSound_Signal(){
//发射超声波信号----------------------------------
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	delay_us(10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	delay_ms(60);
//-----------------------------------------------
}

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
		Car_Stop(CAR_BREAK);	//刹车
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
	Maze_Mode = Obstacle_Avoidance_Mode;
	UltraDis = 700;				//设定超声波信号感知距离
	//发射超声波信号----------------------------------
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	delay_us(10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	delay_ms(60);
	//-----------------------------------------------
	if(Have_OB == Ul_Not_Find_Barrier){
		//Car_forward(40);
		
		//Single_Line(S_Trail_Input, Elude_detect_barrier(), 80, 40, 40);
		Single_Line(S_Trail_Input, Not_Find_Barrier, 80, 40, 40);
	}else{
		Car_Stop(CAR_BREAK);

		TIM_SetCompare1(TIM5,ANGLE4);//Left
		Have_OB = Ul_Not_Find_Barrier;
		delay_ms(1000);								//wait for 舵机
		
		UltraDis = 900;
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		delay_us(10);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		delay_ms(60);


		if(Have_OB == Ul_Not_Find_Barrier){
			//Car_backward(50);	// 后退
			//delay_ms(500);
			Car_Turn_Left(50);	//Left
			delay_ms(370);
			Car_Stop(CAR_BREAK);
			
			TIM_SetCompare1(TIM5,ANGLE2);//Forward
			Have_OB = Ul_Not_Find_Barrier;
		}else{
		
			TIM_SetCompare1(TIM5,ANGLE0);//Right
			Have_OB = Ul_Not_Find_Barrier;
			delay_ms(1000);								//wait for 舵机
		//发射超声波信号------------------------------
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			delay_us(10);
			GPIO_ResetBits(GPIOC,GPIO_Pin_0);
			delay_ms(60);
		//-------------------------------------------
			if(Have_OB == Ul_Not_Find_Barrier){
				//Car_backward(50);	// 后退
				//delay_ms(500);
				Car_Turn_Right(50);	// Right
				delay_ms(370);
				Car_Stop(CAR_BREAK);
				
				TIM_SetCompare1(TIM5,ANGLE2);//Forward
				Have_OB = Ul_Not_Find_Barrier;
			}else{
				Car_Turn_Right(50);	// Turn Around
				delay_ms(700);
				//Car_forward(40);
				Car_Stop(CAR_BREAK);
				
				TIM_SetCompare1(TIM5,ANGLE2);//Forward
				Have_OB = Ul_Not_Find_Barrier;
			}
		}
		delay_ms(1000);								//wait for 舵机
	}
}

void Maze_Track_v2(u8 S_Trail_Input){
	
	if(Elude_detect_barrier() == Not_Find_Barrier){
		Maze_Mode = Tracking_Mode;
		Have_OB = Middle;
		if(TIM_GetCapture1(TIM5) != ANGLE4){
			TIM_SetCompare1(TIM5,ANGLE4);		//Left
			delay_ms(1000);								//wait for 舵机
		}
		Send_UltraSound_Signal();					//发射超声波信号

		if(Have_OB == Middle){
			//Car_forward(40);
			
			Single_Line(S_Trail_Input, Not_Find_Barrier, 90, 40, 40);
		}else if(Have_OB == Too_Near){
			DIFFERENTIAL = 55;
			Car_Become_Right(90);
			//delay_ms(100);
		}else{
			DIFFERENTIAL = 55;
			Car_Become_Left(90);
			//delay_ms(100);
		}
	}else{
		Maze_Mode = Obstacle_Avoidance_Mode;
		DIFFERENTIAL = 90;
		Car_Stop(CAR_BREAK);
		delay_ms(150);
		Car_backward(50);					//倒车
		delay_ms(300);
		Car_Stop(CAR_BREAK);
		if(TIM_GetCapture1(TIM5) != ANGLE4){
			TIM_SetCompare1(TIM5,ANGLE4);		//Left
			delay_ms(1000);								//wait for 舵机
		}
		Send_UltraSound_Signal();			//发射超声波信号

		if(Have_OB == Ul_Not_Find_Barrier){	//左边无障碍
			//Car_backward(50);	// 后退
			//delay_ms(500);
			Car_Turn_Left(50);	//Left
			delay_ms(370);
			Car_Stop(CAR_BREAK);
			
			Have_OB = Ul_Not_Find_Barrier;
		}else{								//左边有障碍
		
			TIM_SetCompare1(TIM5,ANGLE0);	//Right
			Have_OB = Ul_Not_Find_Barrier;
			delay_ms(1000);								//wait for 舵机
			Send_UltraSound_Signal();					//发射超声波信号
			if(Have_OB == Ul_Not_Find_Barrier){	//右边无障碍
				//Car_backward(50);	// 后退
				//delay_ms(500);
				Car_Turn_Right(50);	// Right
				delay_ms(370);
				Car_Stop(CAR_BREAK);
				
				TIM_SetCompare1(TIM5,ANGLE4);	//Forward
				Have_OB = Ul_Not_Find_Barrier;
			}else{
				Car_Turn_Right(50);				// Turn Around
				delay_ms(700);
				//Car_forward(40);
				Car_Stop(CAR_BREAK);
				
				TIM_SetCompare1(TIM5,ANGLE4);	//Left
				Have_OB = Ul_Not_Find_Barrier;
			}
			delay_ms(1000);								//wait for 舵机
		}
	}
}

void Remote_Control(u8 key){
	key = Remote_Scan();
	if(key){ 
		switch(key){ 
			case 104:	//"0"	左转
				Car_Become_Left(80);
				break;
			case 152:	//"100+"	前进
				Car_forward(100);
				break;
			case 176:	//"200+"	右转
				Car_Become_Right(80);
				break;
			case 48:	//"1"	左旋转
				Car_Turn_Left(80);
				break;
			case 24:	//"2"	刹车
				Car_Stop(CAR_BREAK);
				break;
			case 122:	//"3"	右旋转
				Car_Turn_Right(80);
				break;
			case 16:	//"4"	左后转
				Car_Become_Left_Back(80);
				break;
			case 56:	//"5"	后退
				Car_backward(50);
				break;
			case 90:	//"6"	右后转
				Car_Become_Right_Back(80);
				break;
			default:
				break;
		} 
	}else delay_ms(10);
}

int main(void){
	u8 key = 0;
	
	delay_init();
	NVIC_Configuration();	//设置NVIC终端分组2：2
	Elude_Input_Init_JX();	//红外避障模块初始化
	TIM4_PWM_Init_JX();		//pwm电机驱动初始化
	Trail_Input_Init_JX();	//循迹模块初始化
	KEY_Init();				//按键模块初始化
	Ultrasound_Init();		//超声波模块初始化
	Remote_Control_Init();	//红外遥控初始化

	while(1){
	
		u8 S_Elude_Input = 0;
		u8 S_Trail_Input = 0;
		
		switch (Stat){
			
			case Single_Track:
				//Single_Line(S_Trail_Input, Elude_detect_barrier(), 50, 80, 90);
				Single_Line(S_Trail_Input, Not_Find_Barrier, 50, 80, 90);
				break;
					
			case Double_Track:
				//Dubble_Line(S_Trail_Input, Elude_detect_barrier());
				Dubble_Line(S_Trail_Input, Not_Find_Barrier);
				break;
				
			case Maze:
				Maze_Track_v2(S_Trail_Input);
				break;

			case RemoteControl:
				Remote_Control(key);
				break;
			
			default:
				break;
		}
	}
}

