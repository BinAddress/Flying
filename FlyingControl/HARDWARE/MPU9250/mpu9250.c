#include "mpu9250.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "mpuiic.h"
#include "delay.h"

#define FALSE 1
#define TRUE 0

struct class_mpu9250 mpu9250;

//ZRX          
//单字节写入*******************************************

u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	MPU_IIC_Start();
    MPU_IIC_Send_Byte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(MPU_IIC_Wait_Ack()){MPU_IIC_Stop(); return FALSE;}
    MPU_IIC_Send_Byte(REG_Address );   //设置低起始地址      
    MPU_IIC_Wait_Ack();	
    MPU_IIC_Send_Byte(REG_data);
    MPU_IIC_Wait_Ack();   
    MPU_IIC_Stop(); 
    delay_ms(5);
    return TRUE;
}

//单字节读取*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
		MPU_IIC_Start();
    MPU_IIC_Send_Byte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(MPU_IIC_Wait_Ack()){MPU_IIC_Stop();return FALSE;}
    MPU_IIC_Send_Byte((u8) REG_Address);   //设置低起始地址      
    MPU_IIC_Wait_Ack();
    MPU_IIC_Start();
    MPU_IIC_Send_Byte(SlaveAddress+1);
    MPU_IIC_Wait_Ack();

		REG_data= MPU_IIC_Read_Byte(0);
    MPU_IIC_Stop();
    //return TRUE;
	return REG_data;

}		

//初始化MPU9250，根据需要请参考pdf进行修改************************
void Init_MPU9250(void)
{
	MPU_IIC_Init();
/*
   Single_Write(GYRO_ADDRESS,PWR_M, 0x80);   //
   Single_Write(GYRO_ADDRESS,SMPL, 0x07);    //
   Single_Write(GYRO_ADDRESS,DLPF, 0x1E);    //±2000°
   Single_Write(GYRO_ADDRESS,INT_C, 0x00 );  //
   Single_Write(GYRO_ADDRESS,PWR_M, 0x00);   //
*/
  Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);
  //----------------
//	Single_Write(GYRO_ADDRESS,0x6A,0x00);//close Master Mode	

}

//******读取MPU9250数据****************************************
void READ_MPU9250_ACCEL(void)
{ 
		unsigned char BUF[10];
	
   BUF[0]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L); 
   BUF[1]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H);
   mpu9250.accel.x=	(BUF[1]<<8)|BUF[0];
   mpu9250.accel.x/=164; 						   //读取计算X轴数据

   BUF[2]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L);
   BUF[3]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H);
   mpu9250.accel.y=	(BUF[3]<<8)|BUF[2];
   mpu9250.accel.y/=164; 						   //读取计算Y轴数据
   BUF[4]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L);
   BUF[5]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H);
   mpu9250.accel.z=	(BUF[5]<<8)|BUF[4];
   mpu9250.accel.z/=164; 					       //读取计算Z轴数据
 
}

void READ_MPU9250_GYRO(void)
{ 
		unsigned char BUF[10];
   BUF[0]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_L); 
   BUF[1]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_H);
   mpu9250.gyro.x=	(BUF[1]<<8)|BUF[0];
   mpu9250.gyro.x/=16.4; 						   //读取计算X轴数据

   BUF[2]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_L);
   BUF[3]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_H);
   mpu9250.gyro.y=	(BUF[3]<<8)|BUF[2];
   mpu9250.gyro.y/=16.4; 						   //读取计算Y轴数据
   BUF[4]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L);
   BUF[5]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H);
   mpu9250.gyro.z=	(BUF[5]<<8)|BUF[4];
   mpu9250.gyro.z/=16.4; 					       //读取计算Z轴数据
 
 
   BUF[6]=Single_Read(GYRO_ADDRESS,TEMP_OUT_L); 
   BUF[7]=Single_Read(GYRO_ADDRESS,TEMP_OUT_H); 
   mpu9250.temp=(BUF[7]<<8)|BUF[6];
   mpu9250.temp = 35+ ((double) (mpu9250.temp + 13200)) / 280;// 读取计算出温度
}

void READ_MPU9250_MAG(void)
{ 
	 unsigned char BUF[10];
   Single_Write(MAG_ADDRESS,0x37,0x02);//turn on Bypass Mode 
   delay_ms(10);
   Single_Write(MAG_ADDRESS,0x0A,0x01);
   delay_ms(10);	
   BUF[0]=Single_Read (MAG_ADDRESS,MAG_XOUT_L);
   BUF[1]=Single_Read (MAG_ADDRESS,MAG_XOUT_H);
   mpu9250.mag.x=(BUF[1]<<8)|BUF[0];

   BUF[2]=Single_Read(MAG_ADDRESS,MAG_YOUT_L);
   BUF[3]=Single_Read(MAG_ADDRESS,MAG_YOUT_H);
   mpu9250.mag.y=	(BUF[3]<<8)|BUF[2]; //读取计算Y轴数据
	 
   BUF[4]=Single_Read(MAG_ADDRESS,MAG_ZOUT_L);
   BUF[5]=Single_Read(MAG_ADDRESS,MAG_ZOUT_H);
   mpu9250.mag.z=	(BUF[5]<<8)|BUF[4];
 					       //读取计算Z轴数据
}

