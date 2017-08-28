//							OLED
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PD6（SCL）
//              D1   接PD7（SDA）
//              RES  接PD4
//              DC   接PD5
//              CS   接PD3               
//              ----------------------------------------------------------------

//							NRF
//              ----------------------------------------------------------------
//              GND  	电源地
//              VCC  	3.3v电源
//              IRQ   接PE3
//              MISO  接PB14
//              MOSI  接PB15
//              SCK   接PB13
//              CSN   接PE2               
//							CE   	接PE1                              
//              ----------------------------------------------------------------

//							蓝牙
//              ----------------------------------------------------------------
//              GND  	电源地
//              VCC  	3.3v电源
//              TXD   接PA2
//              RXD		接PA3                             
//              ----------------------------------------------------------------

//							摇杆
//              ----------------------------------------------------------------
//              GND  	电源地
//              VCC  	3.3v电源
//              通道1   PC0
//              通道2   PC1
//							通道3   PC2
//				  		通道4   PC3
//              ----------------------------------------------------------------

//							KEY
//              ----------------------------------------------------------------
//							key		PD15
//              ----------------------------------------------------------------

//******************************************************************************/

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "24l01.h" 	 
#include "usart.h"	 
#include "adc.h"
#include "stm32f10x_adc.h"
#include "ano_dt.h"
#include "timer.h"
#include "bin_dt.h"
#include "menu.h"
#include "key.h"
#include "display.h"


 int main(void)
 {	
		
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	 
		oled.Init = OLED_Init;
		oled.Clear = OLED_Clear;
	  oled.English = OLED_ShowString;
		oled.Char = OLED_ShowChar;
		nrf.Init = NRF24L01_Init;
		nrf.Check = NRF24L01_Check;
		nrf.Set_Rx_Mode = NRF24L01_RX_Mode;	 
		nrf.Set_Tx_Mode = NRF24L01_TX_Mode;	 
		hc05.Init = uart_init;
		hc05.PutStrint = printf;
		rocker.Init = Adc_Init;
		rocker.Read = Get_Adc;
		display.Init = Display_Init;
	 
		oled.Init();
		oled.Clear();
		nrf.Init();
		while(nrf.Check());
		hc05.Init(115200);
		rocker.Init();
		display.Init();

		TIM3_Int_Init(9,7199);//10Khz的计数频率，计数到10为1ms

	while(1) 
	{				
			att.pit=rocker.Read(ADC_Channel_10)>>1;
			att.rol=rocker.Read(ADC_Channel_11)>>1;
			att.thr=rocker.Read(ADC_Channel_12)>>1;
			att.yaw=rocker.Read(ADC_Channel_13)>>1;	
					
//			Display();
//			Key_Fun();
	}	  
	
}

