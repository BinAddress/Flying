#include "arch.h"
#include "date.h"
#include "sys.h"

//���ܣ���ʾӢ��
//����1��x����
//����2��y����
//����3������
//����4��������ɫ
//����5��������ɫ
void LCD_Dispaly_English(unsigned int x, unsigned int y,  char *str, unsigned short int color, unsigned short int bkcolor)
{
//    Site_t site = {x,y};   
//    LCD_char(site, *str, color, bkcolor);  //��ʾ8*16�ַ�
}

//���ܣ���ʾ����
//����1��x����
//����2��y����
//����3������
//����4��������ɫ
//����5��������ɫ
void LCD_Dispaly_Chinese(unsigned int x, unsigned int y,  char *str, unsigned short int color, unsigned short int bkcolor)
{
//    u8 i,j,k;
//    u8 tmp_char=0;
//    Site_t site = {x,y}; 
//    const Size_t size   = {LCD_CH_W,LCD_CH_H};

//    LCD_PTLON(site, size);              //����
//    LCD_RAMWR();                        //д�ڴ�

//    for (k=0;k<64;k++)                                      //ѭ��64�Σ���ѯ������ģλ��
//    {
//      if ((CH16[k].GBK[0]==str[0])&&(CH16[k].GBK[1]==str[1]))   //�жϵ�k�����ֵı����Ƿ������뺺��g[2]���
//      {
//          for (i=0;i < 32;i++)
//          {
//                tmp_char=CH16[k].HZ16[i];
//              for(j=0;j<8;j++)
//              {
//                  if(tmp_char & (0x80))
//                  {
//                      LCD_WR_DATA( color );
//                  }
//                  else
//                  {
//                      LCD_WR_DATA( bkcolor );
//                  }
//                  tmp_char <<= 1;
//              }
//          }
//      }
//    }
}
