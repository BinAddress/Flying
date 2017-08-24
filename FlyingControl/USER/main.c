//							NRF
//              ----------------------------------------------------------------
//              GND  	电源地
//              VCC  	3.3v电源
//              IRQ   接PB3
//              MISO  接PB14
//              MOSI  接PB15
//              SCK   接PB13
//              CSN   接PB4               
//							CE   	接PB5                              
//              ----------------------------------------------------------------

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mpu9250.h"
#include "usmart.h"   
#include "24l01.h"
#include "bin_dt.h"


 int main(void)
 {	 	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(500000);	 	//串口初始化为500000
	delay_init();	//延时初始化 
	usmart_dev.init(72);		//初始化USMART
	 
	nrf.Init = NRF24L01_Init;
	nrf.Check = NRF24L01_Check;
	nrf.Set_Rx_Mode = NRF24L01_RX_Mode;	 
	nrf.Set_Tx_Mode = NRF24L01_TX_Mode;
	mpu9250.Init = Init_MPU9250;
	mpu9250.ReadAccel = READ_MPU9250_ACCEL;
	mpu9250.ReadGyro = READ_MPU9250_GYRO;
	mpu9250.ReadMag = READ_MPU9250_MAG;
	
	nrf.Init();
	while(nrf.Check());
	nrf.Set_Rx_Mode();
	mpu9250.Init();
	 


	while(1)
	{
		mpu9250.ReadAccel();
		mpu9250.ReadGyro();
//		mpu9250.ReadMag();
		
		BIN_DT_Data_Exchange();	
	}
		
}



