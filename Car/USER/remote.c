#include "remote.h"

void RemoteControl(){

    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* GPIOA clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = TIM2_Reload_Num;
    TIM_TimeBaseStructure.TIM_Prescaler = TIM2_Frequency_Divide;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x03;  
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    
    /* TIM enable counter */
    TIM_Cmd(TIM2, ENABLE);

    /* Enable the CC2 Interrupt Request */
    TIM_ITConfig(TIM2, TIM_IT_CC2 | TIM_IT_Update, ENABLE);
}

//遥控器接收状态
//[7]:收到了引导码标志
//[6]:得到了一个按键的所有信息
//[5]:保留
//[4]:标记上升沿是否已经被捕获 
//[3:0]:溢出计时器
u8 RmtSta=0; 
u16 Dval; //下降沿时计数器的值
u32 RmtRec=0; //红外接收到的数据 
u8 RmtCnt=0; //按键按下的次数

u8 Remote_Scan(void){
    u8 sta = 0;
    u8 t1, t2;
    if(RmtSta & (1<<6)){
        t1 = RmtRec >>24;
        t2 = (RmtRec >> 16) & 0xff;
    }

}