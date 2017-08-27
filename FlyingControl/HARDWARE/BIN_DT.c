#include "usart.h"
#include "bin_dt.h"
#include "mpu9250.h"
#include "24l01.h"
#include "ano_dt.h"
#include "delay.h"

/////////////////////////////////////////////////////////////////////////////////////
//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

bin_dt_flag_t bin_f;					//��Ҫ�������ݵı�־
u8 bin_data_to_send[32];	//�������ݻ���
u16 bin_aux[6] = {0};

struct class_attitude att = {0}; //ң������Ϣ
struct class_motor motor= {0};	//���ת��
struct class_aircraft aircraft;	//�ɻ���Ϣ
struct class_mpu9250 mpu9250;  //����������

/////////////////////////////////////////////////////////////////////////////////////
//Data_Exchange��������������ݷ������󣬱�����ʵ��ÿ5ms����һ�δ�������������λ�������ڴ˺�����ʵ��
//�˺���Ӧ���û�ÿ1ms����һ��
void BIN_DT_Data_Exchange(void)
{
	static u8 cnt = 0;
	static u8 senser_cnt 	= 10;
	static u8 status_cnt 	= 15;
	static u8 rcdata_cnt 	= 20;
	static u8 motopwm_cnt	= 20;
	static u8 power_cnt		=	50;
	
	if((cnt % senser_cnt) == (senser_cnt-1))
		bin_f.send_senser = 1;	
	
	if((cnt % status_cnt) == (status_cnt-1))
		bin_f.send_status = 1;	
	
	if((cnt % rcdata_cnt) == (rcdata_cnt-1))
		bin_f.send_rcdata = 1;	
	
	if((cnt % motopwm_cnt) == (motopwm_cnt-1))
		bin_f.send_motopwm = 1;	
	
	if((cnt % power_cnt) == (power_cnt-1))
		bin_f.send_power = 1;		
	
	cnt++;
/////////////////////////////////////////////////////////////////////////////////////
	if(bin_f.send_version)
	{
		bin_f.send_version = 0;
//		BIN_DT_Send_Version(4,300,100,400,0);
	}
/////////////////////////////////////////////////////////////////////////////////////
	else if(bin_f.send_status)
	{
		bin_f.send_status = 0;
		BIN_DT_Send_Status(aircraft.rol,aircraft.pit,aircraft.yaw,aircraft.atl,0,0);
	}	
/////////////////////////////////////////////////////////////////////////////////////
	else if(bin_f.send_senser)
	{
		bin_f.send_senser = 0;
		BIN_DT_Send_Senser(mpu9250.accel.x,mpu9250.accel.y,mpu9250.accel.z,
												mpu9250.gyro.x,mpu9250.gyro.y,mpu9250.gyro.z,
												mpu9250.mag.x,mpu9250.mag.y,mpu9250.mag.z,mpu9250.temp);
	}	
/////////////////////////////////////////////////////////////////////////////////////
	else if(bin_f.send_rcdata)
	{
		bin_f.send_rcdata = 0;
//		BIN_DT_Send_RCData(att.thr,att.yaw,att.rol,att.pit,aux[0],aux[1],aux[2],aux[3],aux[4],aux[5]);
	}	
/////////////////////////////////////////////////////////////////////////////////////	
	else if(bin_f.send_motopwm)
	{
		bin_f.send_motopwm = 0;
		BIN_DT_Send_MotoPWM(motor.PWM_1,motor.PWM_2,motor.PWM_3,motor.PWM_4,motor.PWM_5,motor.PWM_6,7,8);
	}	
/////////////////////////////////////////////////////////////////////////////////////
	else if(bin_f.send_power)
	{
		bin_f.send_power = 0;
		BIN_DT_Send_Power(123,456);
	}
/////////////////////////////////////////////////////////////////////////////////////
	else if(bin_f.send_pid1)
	{
		bin_f.send_pid1 = 0;
//		BIN_DT_Send_PID(1,ctrl_1.PID[PIDROLL].kp,ctrl_1.PID[PIDROLL].ki,ctrl_1.PID[PIDROLL].kd,
//											ctrl_1.PID[PIDPITCH].kp,ctrl_1.PID[PIDPITCH].ki,ctrl_1.PID[PIDPITCH].kd,
//											ctrl_1.PID[PIDYAW].kp,ctrl_1.PID[PIDYAW].ki,ctrl_1.PID[PIDYAW].kd);
	}	
/////////////////////////////////////////////////////////////////////////////////////
	else if(bin_f.send_pid2)
	{
		bin_f.send_pid2 = 0;
//		BIN_DT_Send_PID(2,ctrl_1.PID[PID4].kp,ctrl_1.PID[PID4].ki,ctrl_1.PID[PID4].kd,
//											ctrl_1.PID[PID5].kp,ctrl_1.PID[PID5].ki,ctrl_1.PID[PID5].kd,
//											ctrl_1.PID[PID6].kp,ctrl_1.PID[PID6].ki,ctrl_1.PID[PID6].kd);
	}
/////////////////////////////////////////////////////////////////////////////////////
	else if(bin_f.send_pid3)
	{
		bin_f.send_pid3 = 0;
//		BIN_DT_Send_PID(3,ctrl_2.PID[PIDROLL].kp,ctrl_2.PID[PIDROLL].ki,ctrl_2.PID[PIDROLL].kd,
//											ctrl_2.PID[PIDPITCH].kp,ctrl_2.PID[PIDPITCH].ki,ctrl_2.PID[PIDPITCH].kd,
//											ctrl_2.PID[PIDYAW].kp,ctrl_2.PID[PIDYAW].ki,ctrl_2.PID[PIDYAW].kd);
	}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//	Usb_Hid_Send();					
/////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////
//Send_Data������Э�������з������ݹ���ʹ�õ��ķ��ͺ���
//��ֲʱ���û�Ӧ��������Ӧ�õ����������ʹ�õ�ͨ�ŷ�ʽ��ʵ�ִ˺���
void BIN_DT_Send_Data(u8 *dataToSend , u8 length)
{	
		u8 i = 0;
	
		bin_data_to_send[length+1] = 0;
		if(length < 31)
		{
			NRF24L01_TX_Mode();
			for(i = 0; i < 5; i++)
			{
				if(NRF24L01_TxPacket(dataToSend) == TX_OK)
				{
					break;
				}
			}
			NRF24L01_RX_Mode();			
		}
		else
		{
			i = 0;
		}
}

static void BIN_DT_Send_Check(u8 head, u8 check_sum)
{
	u8 sum;
	u8 i;
	
	bin_data_to_send[0]=0xAA;
	bin_data_to_send[1]=0xAA;
	bin_data_to_send[2]=0xEF;
	bin_data_to_send[3]=2;
	bin_data_to_send[4]=head;
	bin_data_to_send[5]=check_sum;
	
	sum = 0;
	for(i=0;i<6;i++)
		sum += bin_data_to_send[i];
	bin_data_to_send[6]=sum;

	BIN_DT_Send_Data(bin_data_to_send, 7);
}

/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Prepare������Э��Ԥ����������Э��ĸ�ʽ�����յ������ݽ���һ�θ�ʽ�Խ�������ʽ��ȷ�Ļ��ٽ������ݽ���
//��ֲʱ���˺���Ӧ���û���������ʹ�õ�ͨ�ŷ�ʽ���е��ã����紮��ÿ�յ�һ�ֽ����ݣ�����ô˺���һ��
//�˺������������ϸ�ʽ������֡�󣬻����е������ݽ�������
void BIN_DT_Data_Receive_Prepare(u8 data)
{
	static u8 RxBuffer[50];
	static u8 _data_len = 0,_data_cnt = 0;
	static u8 state = 0;
	
	if(state==0&&data==0xAA)
	{
		state=1;
		RxBuffer[0]=data;
	}
	else if(state==1&&data==0xAF)
	{
		state=2;
		RxBuffer[1]=data;
	}
	else if(state==2&&data<0XF1)
	{
		state=3;
		RxBuffer[2]=data;
	}
	else if(state==3&&data<50)
	{
		state = 4;
		RxBuffer[3]=data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if(state==4&&_data_len>0)
	{
		_data_len--;
		RxBuffer[4+_data_cnt++]=data;
		if(_data_len==0)
			state = 5;
	}
	else if(state==5)
	{
		state = 0;
		RxBuffer[4+_data_cnt]=data;
		BIN_DT_Data_Receive_Anl(RxBuffer,_data_cnt+5);
	}
	else
		state = 0;
}
/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Anl������Э�����ݽ������������������Ƿ���Э���ʽ��һ������֡���ú��������ȶ�Э�����ݽ���У��
//У��ͨ��������ݽ��н�����ʵ����Ӧ����
//�˺������Բ����û����е��ã��ɺ���Data_Receive_Prepare�Զ�����
void BIN_DT_Data_Receive_Anl(u8 *data_buf,u8 num)
{
	u8 i,sum;
	for(i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		//�ж�sum
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;		//�ж�֡ͷ
	
	if(*(data_buf+2)==0X01)
	{
//		if(*(data_buf+4)==0X01)
//			mpu6050.Acc_CALIBRATE = 1;
//		if(*(data_buf+4)==0X02)
//			mpu6050.Gyro_CALIBRATE = 1;
//		if(*(data_buf+4)==0X03)
//		{
//			mpu6050.Acc_CALIBRATE = 1;		
//			mpu6050.Gyro_CALIBRATE = 1;			
//		}
	}
	
	if(*(data_buf+2)==0X02)
	{
		if(*(data_buf+4)==0X01)
		{
			bin_f.send_pid1 = 1;
			bin_f.send_pid2 = 1;
			bin_f.send_pid3 = 1;
			bin_f.send_pid4 = 1;
			bin_f.send_pid5 = 1;
			bin_f.send_pid6 = 1;
		}
		if(*(data_buf+4)==0X02)
		{
			
		}
		if(*(data_buf+4)==0XA0)		//��ȡ�汾��Ϣ
		{
			bin_f.send_version = 1;
		}
		if(*(data_buf+4)==0XA1)		//�ָ�Ĭ�ϲ���
		{
//			Para_ResetToFactorySetup();
		}
	}

	if(*(data_buf+2)==0X10)								//PID1
    {
//        ctrl_1.PID[PIDROLL].kp  = 0.001*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
//        ctrl_1.PID[PIDROLL].ki  = 0.001*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
//        ctrl_1.PID[PIDROLL].kd  = 0.001*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
//        ctrl_1.PID[PIDPITCH].kp = 0.001*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
//        ctrl_1.PID[PIDPITCH].ki = 0.001*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
//        ctrl_1.PID[PIDPITCH].kd = 0.001*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
//        ctrl_1.PID[PIDYAW].kp 	= 0.001*( (vs16)(*(data_buf+16)<<8)|*(data_buf+17) );
//        ctrl_1.PID[PIDYAW].ki 	= 0.001*( (vs16)(*(data_buf+18)<<8)|*(data_buf+19) );
//        ctrl_1.PID[PIDYAW].kd 	= 0.001*( (vs16)(*(data_buf+20)<<8)|*(data_buf+21) );
        BIN_DT_Send_Check(*(data_buf+2),sum);
//				Param_SavePID();
    }
    if(*(data_buf+2)==0X11)								//PID2
    {
//        ctrl_1.PID[PID4].kp 	= 0.001*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
//        ctrl_1.PID[PID4].ki 	= 0.001*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
//        ctrl_1.PID[PID4].kd 	= 0.001*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
//        ctrl_1.PID[PID5].kp 	= 0.001*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
//        ctrl_1.PID[PID5].ki 	= 0.001*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
//        ctrl_1.PID[PID5].kd 	= 0.001*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
//        ctrl_1.PID[PID6].kp	  = 0.001*( (vs16)(*(data_buf+16)<<8)|*(data_buf+17) );
//        ctrl_1.PID[PID6].ki 	= 0.001*( (vs16)(*(data_buf+18)<<8)|*(data_buf+19) );
//        ctrl_1.PID[PID6].kd 	= 0.001*( (vs16)(*(data_buf+20)<<8)|*(data_buf+21) );
        BIN_DT_Send_Check(*(data_buf+2),sum);
//				Param_SavePID();
    }
    if(*(data_buf+2)==0X12)								//PID3
    {	
//        ctrl_2.PID[PIDROLL].kp  = 0.001*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
//        ctrl_2.PID[PIDROLL].ki  = 0.001*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
//        ctrl_2.PID[PIDROLL].kd  = 0.001*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
//        ctrl_2.PID[PIDPITCH].kp = 0.001*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
//        ctrl_2.PID[PIDPITCH].ki = 0.001*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
//        ctrl_2.PID[PIDPITCH].kd = 0.001*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
//        ctrl_2.PID[PIDYAW].kp 	= 0.001*( (vs16)(*(data_buf+16)<<8)|*(data_buf+17) );
//        ctrl_2.PID[PIDYAW].ki 	= 0.001*( (vs16)(*(data_buf+18)<<8)|*(data_buf+19) );
//        ctrl_2.PID[PIDYAW].kd 	= 0.001*( (vs16)(*(data_buf+20)<<8)|*(data_buf+21) );
        BIN_DT_Send_Check(*(data_buf+2),sum);
//				Param_SavePID();
    }
	if(*(data_buf+2)==0X13)								//PID4
	{
		BIN_DT_Send_Check(*(data_buf+2),sum);
	}
	if(*(data_buf+2)==0X14)								//PID5
	{
		BIN_DT_Send_Check(*(data_buf+2),sum);
	}
	if(*(data_buf+2)==0X15)								//PID6
	{
		BIN_DT_Send_Check(*(data_buf+2),sum);
	}
}

void BIN_DT_Send_Version(u8 hardware_type, u16 hardware_ver,u16 software_ver,u16 protocol_ver,u16 bootloader_ver)
{
	u8 i,sum;
	u8 _cnt=0;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0x00;
	bin_data_to_send[_cnt++]=0;
	
	bin_data_to_send[_cnt++]=hardware_type;
	bin_data_to_send[_cnt++]=BYTE1(hardware_ver);
	bin_data_to_send[_cnt++]=BYTE0(hardware_ver);
	bin_data_to_send[_cnt++]=BYTE1(software_ver);
	bin_data_to_send[_cnt++]=BYTE0(software_ver);
	bin_data_to_send[_cnt++]=BYTE1(protocol_ver);
	bin_data_to_send[_cnt++]=BYTE0(protocol_ver);
	bin_data_to_send[_cnt++]=BYTE1(bootloader_ver);
	bin_data_to_send[_cnt++]=BYTE0(bootloader_ver);
	
	bin_data_to_send[3] = _cnt-4;
	
	sum= 0;
	for(i=0;i<_cnt;i++)
		sum += bin_data_to_send[i];
	bin_data_to_send[_cnt++]=sum;
	
	BIN_DT_Send_Data(bin_data_to_send, _cnt);
}
void BIN_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, s32 alt, u8 fly_model, u8 armed)
{
	u8 _cnt=0;
	vs16 _temp;
	vs32 _temp2 = alt;
	u8 i,sum;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0x01;
	bin_data_to_send[_cnt++]=0;
	
	_temp = (int)(angle_rol);
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_pit);
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_yaw);
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	
	bin_data_to_send[_cnt++]=BYTE3(_temp2);
	bin_data_to_send[_cnt++]=BYTE2(_temp2);
	bin_data_to_send[_cnt++]=BYTE1(_temp2);
	bin_data_to_send[_cnt++]=BYTE0(_temp2);
	
	bin_data_to_send[_cnt++] = fly_model;
	
	bin_data_to_send[_cnt++] = armed;
	
	bin_data_to_send[3] = _cnt-4;
	
	sum= 0;
	for(i=0;i<_cnt;i++)
		sum += bin_data_to_send[i];
	bin_data_to_send[_cnt++]=sum;
	
	BIN_DT_Send_Data(bin_data_to_send, _cnt);
}
void BIN_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z,s32 bar)
{
	u8 _cnt=0;
	vs16 _temp;
	u8 i,sum;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0x02;
	bin_data_to_send[_cnt++]=0;
	
	_temp = a_x;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_y;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_z;	
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = g_x;	
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_y;	
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_z;	
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = m_x;	
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_y;	
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_z;	
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	
	bin_data_to_send[3] = _cnt-4;
	
	sum= 0;
	for(i=0;i<_cnt;i++)
		sum += bin_data_to_send[i];
	bin_data_to_send[_cnt++] = sum;
	
	BIN_DT_Send_Data(bin_data_to_send, _cnt);
}
void BIN_DT_Send_RCData(u16 thr,u16 yaw,u16 rol,u16 pit,u16 bin_aux1,u16 bin_aux2,u16 bin_aux3,u16 bin_aux4,u16 bin_aux5,u16 bin_aux6)
{
	u8 _cnt=0;
	u8 i,sum;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0x03;
	bin_data_to_send[_cnt++]=0;
	bin_data_to_send[_cnt++]=BYTE1(thr);
	bin_data_to_send[_cnt++]=BYTE0(thr);
	bin_data_to_send[_cnt++]=BYTE1(yaw);
	bin_data_to_send[_cnt++]=BYTE0(yaw);
	bin_data_to_send[_cnt++]=BYTE1(rol);
	bin_data_to_send[_cnt++]=BYTE0(rol);
	bin_data_to_send[_cnt++]=BYTE1(pit);
	bin_data_to_send[_cnt++]=BYTE0(pit);
	bin_data_to_send[_cnt++]=BYTE1(bin_aux1);
	bin_data_to_send[_cnt++]=BYTE0(bin_aux1);
	bin_data_to_send[_cnt++]=BYTE1(bin_aux2);
	bin_data_to_send[_cnt++]=BYTE0(bin_aux2);
	bin_data_to_send[_cnt++]=BYTE1(bin_aux3);
	bin_data_to_send[_cnt++]=BYTE0(bin_aux3);
	bin_data_to_send[_cnt++]=BYTE1(bin_aux4);
	bin_data_to_send[_cnt++]=BYTE0(bin_aux4);
	bin_data_to_send[_cnt++]=BYTE1(bin_aux5);
	bin_data_to_send[_cnt++]=BYTE0(bin_aux5);
	bin_data_to_send[_cnt++]=BYTE1(bin_aux6);
	bin_data_to_send[_cnt++]=BYTE0(bin_aux6);

	bin_data_to_send[3] = _cnt-4;
	
	sum= 0;
	for(i=0;i<_cnt;i++)
		sum += bin_data_to_send[i];
	
	bin_data_to_send[_cnt++]=sum;
	
	BIN_DT_Send_Data(bin_data_to_send, _cnt);
}
void BIN_DT_Send_Power(u16 votage, u16 current)
{
	u8 _cnt=0;
	u16 temp;
	u8 i,sum;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0x05;
	bin_data_to_send[_cnt++]=0;
	
	temp = votage;
	bin_data_to_send[_cnt++]=BYTE1(temp);
	bin_data_to_send[_cnt++]=BYTE0(temp);
	temp = current;
	bin_data_to_send[_cnt++]=BYTE1(temp);
	bin_data_to_send[_cnt++]=BYTE0(temp);
	
	bin_data_to_send[3] = _cnt-4;
	
	sum= 0;
	for(i=0;i<_cnt;i++)
		sum += bin_data_to_send[i];
	
	bin_data_to_send[_cnt++]=sum;
	
	BIN_DT_Send_Data(bin_data_to_send, _cnt);
}
void BIN_DT_Send_MotoPWM(u16 m_1,u16 m_2,u16 m_3,u16 m_4,u16 m_5,u16 m_6,u16 m_7,u16 m_8)
{
	u8 _cnt=0;
	u8 i,sum;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0x06;
	bin_data_to_send[_cnt++]=0;
		
	bin_data_to_send[_cnt++]=BYTE1(m_1);
	bin_data_to_send[_cnt++]=BYTE0(m_1);
	bin_data_to_send[_cnt++]=BYTE1(m_2);
	bin_data_to_send[_cnt++]=BYTE0(m_2);
	bin_data_to_send[_cnt++]=BYTE1(m_3);
	bin_data_to_send[_cnt++]=BYTE0(m_3);
	bin_data_to_send[_cnt++]=BYTE1(m_4);
	bin_data_to_send[_cnt++]=BYTE0(m_4);
	bin_data_to_send[_cnt++]=BYTE1(m_5);
	bin_data_to_send[_cnt++]=BYTE0(m_5);
	bin_data_to_send[_cnt++]=BYTE1(m_6);
	bin_data_to_send[_cnt++]=BYTE0(m_6);
	bin_data_to_send[_cnt++]=BYTE1(m_7);
	bin_data_to_send[_cnt++]=BYTE0(m_7);
	bin_data_to_send[_cnt++]=BYTE1(m_8);
	bin_data_to_send[_cnt++]=BYTE0(m_8);
	
	bin_data_to_send[3] = _cnt-4;
	
	sum= 0;
	for(i=0;i<_cnt;i++)
		sum += bin_data_to_send[i];
	
	bin_data_to_send[_cnt++]=sum;
	
	BIN_DT_Send_Data(bin_data_to_send, _cnt);
}
void BIN_DT_Send_PID(u8 group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d)
{
	u8 _cnt=0;
	vs16 _temp;
	u8 i,sum;
	
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0xAA;
	bin_data_to_send[_cnt++]=0x10+group-1;
	bin_data_to_send[_cnt++]=0;
	
	
	_temp = p1_p * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p1_i  * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p1_d  * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_p  * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_i  * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_d * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_p  * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_i  * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_d * 1000;
	bin_data_to_send[_cnt++]=BYTE1(_temp);
	bin_data_to_send[_cnt++]=BYTE0(_temp);
	
	bin_data_to_send[3] = _cnt-4;
	
	sum= 0;
	for(i=0;i<_cnt;i++)
		sum += bin_data_to_send[i];
	
	bin_data_to_send[_cnt++]=sum;

	BIN_DT_Send_Data(bin_data_to_send, _cnt);
}

/******************* (C) COPYRIGHT 2014 BIN TECH *****END OF FILE************/
