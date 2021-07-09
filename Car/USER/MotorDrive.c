#include "MotorDrive.h"

u8 DIFFERENTIAL = 90;

// ��ǰ��
//**************************************
// ��ǰ��=ǰת(�ٶ� = speed%)
//------------------------------------
void Motor_LF_forward(u8 speed)
{
	PB7_Out_PP;
	PB_out(7) = 0;

	PB8_AF_PP;
	TIM_SetCompare3(TIM4, speed);
}
//------------------------------------

// ��ǰ��=��ת(�ٶ� = 1-speed%)
//------------------------------------
void Motor_LF_backward(u8 speed)
{
	PB7_Out_PP;
	PB_out(7) = 1;

	PB8_AF_PP;
	TIM_SetCompare3(TIM4, speed);
}
//------------------------------------


// ��ǰ��=ֹͣ(Ϩ��/ɲ��)
// Wheel_STOP = 0��Ϩ��	1��ɲ��
//------------------------------------
void Motor_LF_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// Ϩ��
	{
		PB7_Out_PP;
		PB_out(7) = 0;
	
		PB8_Out_PP;
		PB_out(8) = 0;
	}
	
	else//if(Wheel_STOP==1)	// ɲ��
	{
		PB7_Out_PP;
		PB_out(7) = 1;
	
		PB8_Out_PP;
		PB_out(8) = 1;
	}
}
//------------------------------------
//**************************************



// ��ǰ��
//**************************************
// ��ǰ��=ǰת(�ٶ� = speed%)
//----------------------------------
void Motor_RF_forward(u8 speed)
{
	PA4_Out_PP;
	PA_out(4) = 0;
	
	PB9_AF_PP;
	TIM_SetCompare4(TIM4, speed);
	
}
//----------------------------------

// ��ǰ��=��ת(�ٶ� = 1-speed%)
//----------------------------------
void Motor_RF_backward(u8 speed)
{
	PB9_AF_PP;
	TIM_SetCompare4(TIM4, speed);
		
	PA4_Out_PP;
	PA_out(4) = 1;
}
//----------------------------------


// ��ǰ��=ֹͣ(Ϩ��/ɲ��)
// Wheel_STOP = 0��Ϩ��	1��ɲ��
//----------------------------------
void Motor_RF_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// Ϩ��
	{
		PA4_Out_PP;
		PA_out(4) = 0;
	
		PB9_Out_PP;
		PB_out(9) = 0;
	}
	
	else//if(Wheel_STOP==1)	// ɲ��
	{
		PA4_Out_PP;
		PA_out(4) = 1;
	
		PB9_Out_PP;
		PB_out(9) = 1;
	}
}
//----------------------------------
//**************************************





// С���˶����
//**************************************
// С��=ֹͣ(Ϩ��/ɲ��)
// Wheel_STOP = 0��Ϩ��	1��ɲ��
//---------------------------------
void Car_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// Ϩ��
	{
		Motor_LF_Stop(0);
		Motor_RF_Stop(0);

	}
	
	else//if(Wheel_STOP==1)	// ɲ��
	{
		Motor_LF_Stop(1);

		Motor_RF_Stop(1);

	}
}
//---------------------------------


// С����ǰ(�ٶ� = speed%)
//---------------------------------
void Car_forward(u8 speed)
{
	Motor_LF_forward(speed);

			
	Motor_RF_forward(speed);

}
//---------------------------------


// С�����(�ٶ� = -speed%)
//---------------------------------
void Car_backward(u8 speed)
{
	Motor_LF_backward(100-speed);

					
	Motor_RF_backward(100-speed);

}
//---------------------------------



// С����xuanת
// ��೵�����ת(�ٶ� = 1-speed%)
// �Ҳ೵����ǰת(�ٶ� = speed%)
//---------------------------------
void Car_Turn_Left(u8 speed)
{
	Motor_LF_backward(100-speed);

	Motor_RF_forward(speed);

}
//---------------------------------


// С����xuanת
// �Ҳ೵�����ת(�ٶ� = 1-speed%)
// ��೵����ǰת(�ٶ� = speed%)
//---------------------------------
void Car_Turn_Right(u8 speed)
{
	Motor_LF_forward(speed);

	Motor_RF_backward(100-speed);

}
//---------------------------------

// С����ת(20<speed)
// ��೵�����ת(�ٶ� = 1-speed%)
// �Ҳ೵����ǰת(�ٶ� = speed%)
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


// С����ת(20<speed)
// �Ҳ೵�����ת(�ٶ� = 1-speed%)
// ��೵����ǰת(�ٶ� = speed%)
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

// С����ת(20<speed)
// ��೵�����ת(�ٶ� = 1-speed%)
// �Ҳ೵����ǰת(�ٶ� = speed%)
//---------------------------------
void Car_Become_Left_Back(u8 speed)
{
	Motor_LF_backward(speed-DIFFERENTIAL);

	Motor_RF_backward(speed);

}
//---------------------------------


// С����ת(20<speed)
// �Ҳ೵�����ת(�ٶ� = 1-speed%)
// ��೵����ǰת(�ٶ� = speed%)
//---------------------------------
void Car_Become_Right_Back(u8 speed)
{
	Motor_LF_backward(speed);

	Motor_RF_backward(speed-DIFFERENTIAL);

}
//---------------------------------