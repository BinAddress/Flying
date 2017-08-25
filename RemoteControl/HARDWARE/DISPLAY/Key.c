#include "key.h"
#include "menu.h"
#include "sys.h"
#include "adc.h"
#include "stm32f10x_adc.h"
#include "delay.h"



void Key_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

char Key_Read(void)
{
	return PDin(15);
}

char Adc_R_Down_Key_Read(void)
{	
	if(Get_Adc(ADC_Channel_13) > 2700)
	{
		delay_ms(10);
		while(Get_Adc(ADC_Channel_13) > 2700);
		return 1;
	}
	return 0;
}

char Adc_R_Up_Key_Read(void)
{	
	if(Get_Adc(ADC_Channel_13) < 1600)
	{
		delay_ms(10);
		while(Get_Adc(ADC_Channel_13) < 1600);
		return 1;
	}
	return 0;
}

//按键读取  去抖
//返回值：按下返回 1 ，否则返回 0 
char Read_Key_Q(void)
{
    if(Key_Read() == 0)
    {
        delay_ms(10);
        if(Key_Read() == 0)
        {
            while(Key_Read() == 0);
            return 1;
        }
    }
    return 0;
}
