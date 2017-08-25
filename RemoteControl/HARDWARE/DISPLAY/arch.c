#include "arch.h"
#include "date.h"
#include "sys.h"

//功能：显示英语
//参数1：x坐标
//参数2：y坐标
//参数3：数据
//参数4：字体颜色
//参数5：背景颜色
void LCD_Dispaly_English(unsigned int x, unsigned int y,  char *str, unsigned short int color, unsigned short int bkcolor)
{
//    Site_t site = {x,y};   
//    LCD_char(site, *str, color, bkcolor);  //显示8*16字符
}

//功能：显示汉字
//参数1：x坐标
//参数2：y坐标
//参数3：数据
//参数4：字体颜色
//参数5：背景颜色
void LCD_Dispaly_Chinese(unsigned int x, unsigned int y,  char *str, unsigned short int color, unsigned short int bkcolor)
{
//    u8 i,j,k;
//    u8 tmp_char=0;
//    Site_t site = {x,y}; 
//    const Size_t size   = {LCD_CH_W,LCD_CH_H};

//    LCD_PTLON(site, size);              //开窗
//    LCD_RAMWR();                        //写内存

//    for (k=0;k<64;k++)                                      //循环64次，查询汉字字模位置
//    {
//      if ((CH16[k].GBK[0]==str[0])&&(CH16[k].GBK[1]==str[1]))   //判断第k个汉字的编码是否与输入汉字g[2]相等
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
