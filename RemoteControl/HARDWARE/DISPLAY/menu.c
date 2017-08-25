#include "menu.h"
#include "arch.h"
#include "key.h"
#include "delay.h"

void float_to_char(char *ch , float data); 
void uint_to_char(char *ch, unsigned int data);
void LCD_Dispaly_String(unsigned int x, unsigned int y,  char *str, unsigned short int color, unsigned short int bkcolor);

void Display_Init(void) //����ָ�븳ֵ
{

	display.key[0].Init = Key_Init;
	display.key[0].Read = Key_Read;
	
	display.key[0].Init();
}

void Display(void)
{
    if(display.flag)                         
    {
       display.Clear();
			 display.menu[display.show].Init();
       display.flag = 0;
    }
		display.menu[display.show].Show();
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
void LCD_Dispaly_String(unsigned int x, unsigned int y,  char *str, unsigned short int color, unsigned short int bkcolor)
{  
//#define MAX_CHAR_POSX (LCD_W-8)
//#define MAX_CHAR_POSY (LCD_H-16)
//  
//    while(*str)
//    {
//        if(x > MAX_CHAR_POSX )
//        {
//            //����
//            x = 0;
//            y += 16;
//        }
//        if(y > MAX_CHAR_POSY )
//        {
//            //һ��
//            y = 0;
//            x = 0;
//        }

//        if( *str < 0x80)                             //�ж�sָ����ַ����е�ĳ�ַ��ı���ֵ�Ƿ�С��128,���С��,��ΪASCII�ַ�
//            {
//             LCD_Dispaly_English(x, y, str, color, bkcolor); 
//             x += 8;
//             str++;                             //ָ���1
//                }
//        else
//            {
//             LCD_Dispaly_Chinese(x, y, str, color, bkcolor); 
//             str+=2;                                 //��Ϊ����Ϊ����Ϊ2�ֽڣ�ָ���2,��ʾ16x16����λ�ü�2
//             x += 16;
//             }
//    }
}

//������ȡ  ȥ��
//����ֵ�����·��� 1 �����򷵻� 0 
unsigned char Read_Key_Q(char date)
{
    if(display.key[date].Read() == 0)
    {
        delay_ms(10);
        if(display.key[date].Read() == 0)
        {
            while(display.key[date].Read() == 0);
            return 1;
        }
    }
    return 0;
}

void Key_Fun(void)
{
	u8 i = 0;
	for(i = 0; i < KEY_NUMBER; i++)
	{
		if(Read_Key_Q(i))
		{
				display.key[i].menu[display.show]();
				display.flag = 1;
		}
	}
}




