#ifndef __USER_MENU_H__
#define __USER_MENU_H__

#define DISPLAY_NUMBER  5 //界面总数
#define KEY_NUMBER	3 //按键个数

struct class_key{
void (*Init)(void);					//初始化
char (*Read)(void);
void (*menu[DISPLAY_NUMBER])(void);
};

struct class_menu{
char max;						//当前界面的最大选项
char choose;				//当前界面选择项
void (*Init)(void);	//界面初始化
void (*Show)(void); //界面循环显示
};

struct class_display{
char 	show;									//当前显示界面
char  flag;									//当前界面是否刷新
void (*Init)(void);					//初始化
void (*Clear)(void);				//清屏函数
struct class_menu menu[DISPLAY_NUMBER]; //界面函数
struct class_key key[KEY_NUMBER];				//按键控制函数
};

extern struct class_display display;

void Display(void);
void Key_Fun(void);

#endif
