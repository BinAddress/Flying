#include "menu.h"
#include "arch.h"
#include "key.h"
#include "delay.h"

struct class_display display;



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

void Key_Fun(void)
{
	u8 i = 0;
	for(i = 0; i < KEY_NUMBER; i++)
	{
		if(display.key[i].Read())
		{
				display.key[i].menu[display.show]();
				display.flag = 1;
		}
	}
}
