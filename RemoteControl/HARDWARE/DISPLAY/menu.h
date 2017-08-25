#ifndef __USER_MENU_H__
#define __USER_MENU_H__

#define DISPLAY_NUMBER  5 //��������
#define KEY_NUMBER	1 //��������

struct class_key{
void (*Init)(void);					//��ʼ��
char (*Read)(void);
void (*menu[DISPLAY_NUMBER])(void);
};

struct class_menu{
char max;						//��ǰ��������ѡ��
char choose;				//��ǰ����ѡ����
void (*Init)(void);	//�����ʼ��
void (*Show)(void); //����ѭ����ʾ
};

typedef struct class_display{
char 	show;									//��ǰ��ʾ����
char  flag;									//��ǰ�����Ƿ�ˢ��
void (*Init)(void);					//��ʼ��
void (*Clear)(void);				//��������
struct class_menu menu[DISPLAY_NUMBER]; //���溯��
struct class_key key[KEY_NUMBER];				//�������ƺ���
}class_display;

static class_display display;

void Display(void);
void Display_Init(void);

#endif
