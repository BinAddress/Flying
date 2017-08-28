//							OLED
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PD6��SCL��
//              D1   ��PD7��SDA��
//              RES  ��PD4
//              DC   ��PD5
//              CS   ��PD3               
//              ----------------------------------------------------------------

//							NRF
//              ----------------------------------------------------------------
//              GND  	��Դ��
//              VCC  	3.3v��Դ
//              IRQ   ��PE3
//              MISO  ��PB14
//              MOSI  ��PB15
//              SCK   ��PB13
//              CSN   ��PE2               
//							CE   	��PE1                              
//              ----------------------------------------------------------------

//							����
//              ----------------------------------------------------------------
//              GND  	��Դ��
//              VCC  	3.3v��Դ
//              TXD   ��PA2
//              RXD		��PA3                             
//              ----------------------------------------------------------------

//							ҡ��
//              ----------------------------------------------------------------
//              GND  	��Դ��
//              VCC  	3.3v��Դ
//              ͨ��1   PC0
//              ͨ��2   PC1
//							ͨ��3   PC2
//				  		ͨ��4   PC3
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
		
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	 
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

		TIM3_Int_Init(9,7199);//10Khz�ļ���Ƶ�ʣ�������10Ϊ1ms

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

