//							NRF
//              ----------------------------------------------------------------
//              GND  	��Դ��
//              VCC  	3.3v��Դ
//              IRQ   ��PB3
//              MISO  ��PB14
//              MOSI  ��PB15
//              SCK   ��PB13
//              CSN   ��PB4               
//							CE   	��PB5                              
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(500000);	 	//���ڳ�ʼ��Ϊ500000
	delay_init();	//��ʱ��ʼ�� 
	usmart_dev.init(72);		//��ʼ��USMART
	 
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



