//							NRF
//              ----------------------------------------------------------------
//              GND  	��Դ��
//              VCC  	3.3v��Դ
//              IRQ   ��PB5
//              MISO  ��PA6
//              MOSI  ��PA7
//              SCK   ��PA5
//              CSN   ��PA2               
//							CE   	��PA3                              
//              ----------------------------------------------------------------

//							MPU9250
//              ----------------------------------------------------------------
//              GND  	��Դ��
//              VCC  	3.3v��Դ
//              FSYNC	3.3V
//              NCS		��
//							INT 	GND
//							AD0 	��
//							ECL 	��
//							EDA 	��
//							SDA 	PB7
//							SCL 	PB6
//              ----------------------------------------------------------------
//							
//							Moter
//              ----------------------------------------------------------------
//							PWM1 PB0
//							PWM2 PB1
//							PWM3 PA8
//							PWM4 PA9
//							PWM5 PA10
//							PWM6 PA11
//              ----------------------------------------------------------------

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "mpu9250.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "24l01.h"
#include "bin_dt.h"
#include "ano_dt.h"
#include "pwm.h"

int main(void)
{
	float pitch,roll,yaw; 	        //ŷ����

	delay_init();                //��ʼ����ʱ����
//	uart_init(500000);              //��ʼ��USART
	
	PWM_Init();
	
//	while(mpu_dmp_init())
//	{   
// 		delay_ms(200);
//	}
	
	nrf.Init = NRF24L01_Init;
	nrf.Check = NRF24L01_Check;
	nrf.Set_Rx_Mode = NRF24L01_RX_Mode;	 
	nrf.Set_Tx_Mode = NRF24L01_TX_Mode;
	 
	nrf.Init();
	while(nrf.Check());
	nrf.Set_Rx_Mode();
	
   
    while(1)
    {
//			if(mpu_mpl_get_data(&pitch,&roll,&yaw)==0)
//			{
//					MPU_Get_Accelerometer(&mpu9250.accel.x,&mpu9250.accel.y,&mpu9250.accel.z);	//�õ����ٶȴ���������
//					MPU_Get_Gyroscope(&mpu9250.gyro.x,&mpu9250.gyro.y,&mpu9250.gyro.z);	//�õ�����������
//					MPU_Get_Magnetometer(&mpu9250.mag.x,&mpu9250.mag.y,&mpu9250.mag.z);			
//				
//					aircraft.pit = (short int)(pitch*100);
//					aircraft.rol = (short int)(roll*100);
//					aircraft.yaw = (short int)(yaw*100);
//			
//					
//			}
			
			motor.PWM_1 = 1000;
			motor.PWM_2 = 2000;
			motor.PWM_3 = 3000;
			motor.PWM_4 = 4000;
			motor.PWM_5 = 5000;
			motor.PWM_6 = 6000;
			
			BIN_DT_Data_Exchange();
			PWM_Duty_Set();
			
	  }
}
