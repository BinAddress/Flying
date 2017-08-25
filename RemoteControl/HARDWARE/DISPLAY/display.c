#include "display.h"
#include "menu.h"
#include "key.h"
#include "delay.h"
#include "oled.h"
#include "adc.h"
#include "ano_dt.h"

void float_to_char(char *ch , float data); 
void uint_to_char(char *ch, unsigned int data);
void LCD_Dispaly_String(unsigned int x, unsigned int y,  char *str);

void main_menu(void) //���˵�
{
	
}

void return_main(void)
{
	display.show = 0;
}

void menu_nop(void)
{

}

void main_menu_init(void) //���˵�
{
	LCD_Dispaly_String(25,0,"Flying");
	LCD_Dispaly_String(25,2,"Remote");
	LCD_Dispaly_String(25,4,"PID");
	LCD_Dispaly_String(25,6,"Info");
	
	LCD_Dispaly_String(10,display.menu[0].choose * 2,">");
}

void key0_main_menu(void)
{
	display.show = display.menu[0].choose+1;
}

void key_r_down_main_menu(void)
{
	if(++display.menu[0].choose == display.menu[0].max)
	{
		display.menu[0].choose = 0;
	}
}

void key_r_up_main_menu(void)
{
	if(display.menu[0].choose > 0)
	{
		display.menu[0].choose--;
	}
	else
	{
		display.menu[0].choose = 3;
	}
}

void flying_menu_init(void)
{
	LCD_Dispaly_String(0,0,"pit:");
	LCD_Dispaly_String(0,2,"rol:");
	LCD_Dispaly_String(0,4,"yaw:");
	LCD_Dispaly_String(0,6,"thr:");
}

void flying_menu(void)
{
	OLED_ShowNum(32,0,(short int)(aircraft.pit/100),3,16);
	OLED_ShowNum(32,2,(short int)(aircraft.rol/100),3,16);
	OLED_ShowNum(32,4,(short int)(aircraft.yaw/100),3,16);
	OLED_ShowNum(32,6,(short int)(aircraft.atl/100),3,16);
}

void remote_menu_init(void)
{

}

void remote_menu(void)
{

}

void pid_menu_init(void)
{

}

void pid_menu(void)
{

}

void info_menu_init(void)
{

}

void info_menu(void)
{

}

void Display_Init(void) //����ָ�븳ֵ
{
	display.Clear = OLED_Clear;
	
	display.menu[0].Init = main_menu_init; //������
	display.menu[0].Show = main_menu;
	display.menu[0].choose = 0;
	display.menu[0].max = 4;
	
	display.menu[1].Init = flying_menu_init;	//��������Ϣ
	display.menu[1].Show = flying_menu;
	display.menu[1].choose = 0;
	display.menu[1].max = 0;
	
	display.menu[2].Init = remote_menu_init; //ң������Ϣ
	display.menu[2].Show = remote_menu;
	display.menu[2].choose = 0;
	display.menu[2].max = 0;
	
	display.menu[3].Init = pid_menu_init; //�汾��Ϣ
	display.menu[3].Show = pid_menu;
	display.menu[3].choose = 0;
	display.menu[3].max = 0;	
	
	display.menu[4].Init = info_menu_init; //�汾��Ϣ
	display.menu[4].Show = info_menu;
	display.menu[4].choose = 0;
	display.menu[4].max = 0;	


	display.key[0].Init = Key_Init;
	display.key[0].Read = Read_Key_Q;
	display.key[0].menu[0] = key0_main_menu;
	display.key[0].menu[1] = return_main;
	display.key[0].menu[2] = return_main;
	display.key[0].menu[3] = return_main;
	display.key[0].menu[4] = return_main;
	
	display.key[1].Init = Adc_Init;
	display.key[1].Read = Adc_R_Down_Key_Read;
	display.key[1].menu[0] = key_r_down_main_menu;
	display.key[1].menu[1] = menu_nop;
	display.key[1].menu[2] = menu_nop;
	display.key[1].menu[3] = menu_nop;
	display.key[1].menu[4] = menu_nop;
	
	display.key[2].Init = Adc_Init;
	display.key[2].Read = Adc_R_Up_Key_Read;
	display.key[2].menu[0] = key_r_up_main_menu;
	display.key[2].menu[1] = menu_nop;
	display.key[2].menu[2] = menu_nop;
	display.key[2].menu[3] = menu_nop;
	display.key[2].menu[4] = menu_nop;
	
	display.flag = 1; //����ˢ�½���
	display.show = 0; //ˢ�½��� 0
	display.key[0].Init();
}


void float_to_char(char *ch , float data)
{
  ch[0] = (char)(((int)(data/1000))%10) + 0x30;
  ch[1] = (char)(((int)(data/100))%10) + 0x30;
  ch[2] = (char)(((int)(data/10))%10) + 0x30;
  ch[3] = (char)(((int)(data))%10) + 0x30;
  ch[4] = '.';
  ch[5] = (char)(((int)(data*10))%10) + 0x30;
  ch[6] = (char)(((int)(data*100))%10) + 0x30;
}

void uint_to_char(char *ch, unsigned int data)
{
  ch[0] = (char)(((int)(data/10000))%10) + 0x30;
  ch[1] = (char)(((int)(data/1000))%10) + 0x30;
  ch[2] = (char)(((int)(data/100))%10) + 0x30;
  ch[3] = (char)(((int)(data/10))%10) + 0x30;
  ch[4] = (char)(((int)(data))%10) + 0x30;
}



//���ܣ���ʾ�ַ���
//����1��x����
//����2��y����
//����3��str      ����
//����4��Color   ������ɫ
//����5��bkColor ����ɫ
void LCD_Dispaly_String(unsigned int x, unsigned int y,  char *str)
{  
#define MAX_CHAR_POSX (128-8)
#define MAX_CHAR_POSY (64-16)
  
    while(*str)
    {
        if(x > MAX_CHAR_POSX )
        {
            //����
            x = 0;
            y += 16;
        }
        if(y > MAX_CHAR_POSY )
        {
            //һ��
            y = 0;
            x = 0;
        }

        if( *str < 0x80)                             //�ж�sָ����ַ����е�ĳ�ַ��ı���ֵ�Ƿ�С��128,���С��,��ΪASCII�ַ�
            {
             OLED_ShowChar(x,y,*str);
             x += 8;
             str++;                             //ָ���1
                }
        else
            {
//             LCD_Dispaly_Chinese(x, y, str, color, bkcolor); 
             str+=2;                                 //��Ϊ����Ϊ����Ϊ2�ֽڣ�ָ���2,��ʾ16x16����λ�ü�2
             x += 16;
             }
    }
}



