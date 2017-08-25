#include "key.h"
#include "menu.h"
#include "sys.h"

void Kye1_Fun(void);
void Kye2_Fun(void);
void Kye3_Fun(void);
void Kye4_Fun(void);
void Kye5_Fun(void);

void Key_Up_Show0(void);
void Key_Up_Show1(void);
void Key_Up_Show2(void);
void Key_Up_Show3(void);
void Key_Up_Show4(void);
void Key_Up_Show5(void);
void Key_Up_Show6(void);
void Key_Up_Show7(void);
void Key_Up_Show8(void);
void Key_Up_Show9(void);
void Key_Up_Show10(void);
void Key_Up_Show11(void);
void Key_Up_Show12(void);
void Key_Up_Show13(void);
void Key_Up_Show14(void);
void Key_Up_Show15(void);

void Key_DOWN_Show0(void);
void Key_DOWN_Show1(void);
void Key_DOWN_Show2(void);
void Key_DOWN_Show3(void);
void Key_DOWN_Show4(void);
void Key_DOWN_Show5(void);
void Key_DOWN_Show6(void);
void Key_DOWN_Show7(void);
void Key_DOWN_Show8(void);
void Key_DOWN_Show9(void);
void Key_DOWN_Show10(void);
void Key_DOWN_Show11(void);
void Key_DOWN_Show12(void);
void Key_DOWN_Show13(void);
void Key_DOWN_Show14(void);
void Key_DOWN_Show15(void);

void Key_LIFT_Show0(void);
void Key_LIFT_Show1(void);
void Key_LIFT_Show2(void);
void Key_LIFT_Show3(void);
void Key_LIFT_Show4(void);
void Key_LIFT_Show5(void);
void Key_LIFT_Show6(void);
void Key_LIFT_Show7(void);
void Key_LIFT_Show8(void);
void Key_LIFT_Show9(void);
void Key_LIFT_Show10(void);
void Key_LIFT_Show11(void);
void Key_LIFT_Show12(void);
void Key_LIFT_Show13(void);
void Key_LIFT_Show14(void);
void Key_LIFT_Show15(void);

void Key_RIGHT_Show0(void);
void Key_RIGHT_Show1(void);
void Key_RIGHT_Show2(void);
void Key_RIGHT_Show3(void);
void Key_RIGHT_Show4(void);
void Key_RIGHT_Show5(void);
void Key_RIGHT_Show6(void);
void Key_RIGHT_Show7(void);
void Key_RIGHT_Show8(void);
void Key_RIGHT_Show9(void);
void Key_RIGHT_Show10(void);
void Key_RIGHT_Show11(void);
void Key_RIGHT_Show12(void);
void Key_RIGHT_Show13(void);
void Key_RIGHT_Show14(void);
void Key_RIGHT_Show15(void);

void Key_CENTRE_Show0(void);
void Key_CENTRE_Show1(void);
void Key_CENTRE_Show2(void);
void Key_CENTRE_Show3(void);
void Key_CENTRE_Show4(void);
void Key_CENTRE_Show5(void);
void Key_CENTRE_Show6(void);
void Key_CENTRE_Show7(void);
void Key_CENTRE_Show8(void);
void Key_CENTRE_Show9(void);
void Key_CENTRE_Show10(void);
void Key_CENTRE_Show11(void);
void Key_CENTRE_Show12(void);
void Key_CENTRE_Show13(void);
void Key_CENTRE_Show14(void);
void Key_CENTRE_Show15(void);


void Key_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

char Key_Read(void)
{
	return PDin(15);
}

