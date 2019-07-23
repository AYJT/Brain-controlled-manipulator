#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "usart.h"
#include "timer.h"
void GPIO_Configuration(void);
void RCC_Configuration(void);
  int main(void)
 {	

	 RCC_Configuration();
	 GPIO_Configuration();//端口初始化
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration();// 设置中断优先级分组
	uart_init(9600);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
 	TIM3_PWM_Init(19999,71);	 //不分频。PWM频率=72000000/900=80Khz舵机PB1
	TIM5_PWM_Init(7199,0);		 //不分频。PWM频率=72000000/900=80Khz直线电机正转，伸展PA0
	 TIM1_PWM_Init(7199,0);//直线电机反转，收缩PA8
 while(1)
		 {
			  GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_4);
	 if(USART_ReceiveData(USART1)==0x01)
	 {
	
		TIM_SetCompare4(TIM3,600);
	 //直线行程电机
	 GPIO_SetBits(GPIOD,GPIO_Pin_0);
			
			
		 delay_ms(1800); 
		 //delay_ms(600); 
		  GPIO_ResetBits(GPIOD,GPIO_Pin_0);
	USART_ReceiveData(USART1)==0;
		
		 } 
	 
		 
		 if(USART_ReceiveData(USART1)==0x02)
	 {
		
	//舵机控?
	
	//舵机控制
		TIM_SetCompare4(TIM3,1200);
	 //直线行程电机
	GPIO_SetBits(GPIOD,GPIO_Pin_1);
			
		 delay_ms(1800);    
		 //delay_ms(1800); 
		// delay_ms(600); 
		  GPIO_ResetBits(GPIOD,GPIO_Pin_1);
		 } 
	 
		 
	}	 
 
}
void GPIO_Configuration(void)
{
	
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14 //D0
								|GPIO_Pin_15 //D1
								|GPIO_Pin_0	 //D2
								|GPIO_Pin_1	 //D3
								|GPIO_Pin_3	 //D13
								|GPIO_Pin_4	 //D14
								|GPIO_Pin_10;//D15
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9);

}
void RCC_Configuration(void)
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}

