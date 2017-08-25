#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "mpu9250.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "24l01.h"
#include "bin_dt.h"

//??1??1??? 
//c:??????
void usart1_send_char(u8 c)
{
	while((USART1->SR&0X40)==0);//?????????   
	USART1->DR=c;   	
} 

//??????????????(V2.6??)
//fun:???. 0XA0~0XAF
//data:?????,??28??!!
//len:data???????
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//??28???? 
	send_buf[len+3]=0;	//?????
	send_buf[0]=0X88;	//??
	send_buf[1]=fun;	//???
	send_buf[2]=len;	//????
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//????
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//?????	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//???????1 
}

//????1?????????????
//aacx,aacy,aacz:x,y,z???????????
//gyrox,gyroy,gyroz:x,y,z???????????
//roll:???.??0.01?? -18000 -> 18000 ?? -180.00  ->  180.00?
//pitch:???.?? 0.01??-9000 - 9000 ?? -90.00 -> 90.00 ?
//yaw:???.???0.1? 0 -> 3600  ?? 0 -> 360.0?
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//?0
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//?????,0XAF
}   

int main(void)
{
	float pitch,roll,yaw; 	        //欧拉角
	short aacx,aacy,aacz;	        //加速度传感器原始数据
	short gyrox,gyroy,gyroz;        //陀螺仪原始数据 
            
	delay_init();                //初始化延时函数
	uart_init(500000);              //初始化USART
	
	LED_Init();                     //初始化LED 
	while(mpu_dmp_init())
	{   
 		delay_ms(200);
//		LED0=!LED0;//DS0闪烁 
	}
	
	nrf.Init = NRF24L01_Init;
	nrf.Check = NRF24L01_Check;
	nrf.Set_Rx_Mode = NRF24L01_RX_Mode;	 
	nrf.Set_Tx_Mode = NRF24L01_TX_Mode;
	 

	
//	nrf.Init();
//	while(nrf.Check());
//	nrf.Set_Rx_Mode();
	
   
    while(1)
    {
			if(mpu_mpl_get_data(&pitch,&roll,&yaw)==0)
			{
					MPU_Get_Accelerometer(&mpu9250.accel.x,&mpu9250.accel.y,&mpu9250.accel.z);	//得到加速度传感器数据
					MPU_Get_Gyroscope(&mpu9250.gyro.x,&mpu9250.gyro.y,&mpu9250.gyro.x);	//得到陀螺仪数据
					
				//aircraft.rol=-(int)(roll*100);
				//aircraft.pit=(int)(pitch*10);
//				aircraft.yaw=(int)(yaw*10);

//		BIN_DT_Data_Exchange();
//					mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//发送加速度+陀螺仪原始数据
					usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,-(int)(roll*100),(int)(pitch*100),-(int)(yaw*10));
//		      LED1=!LED1;
			}
//			else {LED0=!LED0;delay_ms(200);}
	  }
}
