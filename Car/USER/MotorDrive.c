#include "MotorDrive.h"

u8 DIFFERENTIAL = 90;

// 左前轮
//**************************************
// 左前轮=前转(速度 = speed%)
//------------------------------------
void Motor_LF_forward(u8 speed)
{
	PB7_Out_PP;
	PB_out(7) = 0;

	PB8_AF_PP;
	TIM_SetCompare3(TIM4, speed);
}
//------------------------------------

// 左前轮=后转(速度 = 1-speed%)
//------------------------------------
void Motor_LF_backward(u8 speed)
{
	PB7_Out_PP;
	PB_out(7) = 1;

	PB8_AF_PP;
	TIM_SetCompare3(TIM4, speed);
}
//------------------------------------


// 左前轮=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//------------------------------------
void Motor_LF_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		PB7_Out_PP;
		PB_out(7) = 0;
	
		PB8_Out_PP;
		PB_out(8) = 0;
	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		PB7_Out_PP;
		PB_out(7) = 1;
	
		PB8_Out_PP;
		PB_out(8) = 1;
	}
}
//------------------------------------
//**************************************



// 右前轮
//**************************************
// 右前轮=前转(速度 = speed%)
//----------------------------------
void Motor_RF_forward(u8 speed)
{
	PA4_Out_PP;
	PA_out(4) = 0;
	
	PB9_AF_PP;
	TIM_SetCompare4(TIM4, speed);
	
}
//----------------------------------

// 右前轮=后转(速度 = 1-speed%)
//----------------------------------
void Motor_RF_backward(u8 speed)
{
	PB9_AF_PP;
	TIM_SetCompare4(TIM4, speed);
		
	PA4_Out_PP;
	PA_out(4) = 1;
}
//----------------------------------


// 右前轮=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//----------------------------------
void Motor_RF_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		PA4_Out_PP;
		PA_out(4) = 0;
	
		PB9_Out_PP;
		PB_out(9) = 0;
	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		PA4_Out_PP;
		PA_out(4) = 1;
	
		PB9_Out_PP;
		PB_out(9) = 1;
	}
}
//----------------------------------
//**************************************





// 小车运动情况
//**************************************
// 小车=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//---------------------------------
void Car_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		Motor_LF_Stop(0);
		Motor_RF_Stop(0);

	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		Motor_LF_Stop(1);

		Motor_RF_Stop(1);

	}
}
//---------------------------------


// 小车向前(速度 = speed%)
//---------------------------------
void Car_forward(u8 speed)
{
	Motor_LF_forward(speed);

			
	Motor_RF_forward(speed);

}
//---------------------------------


// 小车向后(速度 = -speed%)
//---------------------------------
void Car_backward(u8 speed)
{
	Motor_LF_backward(100-speed);

					
	Motor_RF_backward(100-speed);

}
//---------------------------------



// 小车左xuan转
// 左侧车轮向后转(速度 = 1-speed%)
// 右侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Turn_Left(u8 speed)
{
	Motor_LF_backward(100-speed);

	Motor_RF_forward(speed);

}
//---------------------------------


// 小车右xuan转
// 右侧车轮向后转(速度 = 1-speed%)
// 左侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Turn_Right(u8 speed)
{
	Motor_LF_forward(speed);

	Motor_RF_backward(100-speed);

}
//---------------------------------

// 小车左转(20<speed)
// 左侧车轮向后转(速度 = 1-speed%)
// 右侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Become_Left(u8 speed)
{
	if(speed-DIFFERENTIAL >= 0){
		Motor_LF_forward(speed-DIFFERENTIAL);
		Motor_RF_forward(speed);
	}else{
		Motor_LF_backward(100-(-speed+DIFFERENTIAL));
		Motor_RF_forward(speed);
	}
}
//---------------------------------


// 小车右转(20<speed)
// 右侧车轮向后转(速度 = 1-speed%)
// 左侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Become_Right(u8 speed)
{
	if(speed-DIFFERENTIAL >= 0){
		Motor_LF_forward(speed);
		Motor_RF_forward(speed-DIFFERENTIAL);
	}else{
		Motor_LF_forward(speed);
		Motor_RF_backward(100-(-speed+DIFFERENTIAL));
	}

}
//---------------------------------

// 小车左转(20<speed)
// 左侧车轮向后转(速度 = 1-speed%)
// 右侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Become_Left_Back(u8 speed)
{
	Motor_LF_backward(speed-DIFFERENTIAL);

	Motor_RF_backward(speed);

}
//---------------------------------


// 小车右转(20<speed)
// 右侧车轮向后转(速度 = 1-speed%)
// 左侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Become_Right_Back(u8 speed)
{
	Motor_LF_backward(speed);

	Motor_RF_backward(speed-DIFFERENTIAL);

}
//---------------------------------