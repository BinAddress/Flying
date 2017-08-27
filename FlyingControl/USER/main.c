//							NRF
//              ----------------------------------------------------------------
//              GND  	电源地
//              VCC  	3.3v电源
//              IRQ   接PB5
//              MISO  接PA6
//              MOSI  接PA7
//              SCK   接PA5
//              CSN   接PA2               
//							CE   	接PA3                              
//              ----------------------------------------------------------------

//							MPU9250
//              ----------------------------------------------------------------
//              GND  	电源地
//              VCC  	3.3v电源
//              FSYNC	3.3V
//              NCS		空
//							INT 	GND
//							AD0 	空
//							ECL 	空
//							EDA 	空
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
	float pitch,roll,yaw; 	        //欧拉角

	delay_init();                //初始化延时函数
//	uart_init(500000);              //初始化USART
	
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
//					MPU_Get_Accelerometer(&mpu9250.accel.x,&mpu9250.accel.y,&mpu9250.accel.z);	//得到加速度传感器数据
//					MPU_Get_Gyroscope(&mpu9250.gyro.x,&mpu9250.gyro.y,&mpu9250.gyro.z);	//得到陀螺仪数据
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
