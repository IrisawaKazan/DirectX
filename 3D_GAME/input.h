//==============================================================
//
//[input.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,//�\���L�[(��)
	JOYKEY_DOWN,  //�\���L�[(��)
	JOYKEY_LEFT,  //�\���L�[(��)
	JOYKEY_RIGHT, //�\���L�[(�E)
	JOYKEY_START, //
	JOYKEY_BACK,  //
	JOYKEY_L3,    //
	JOYKEY_R3,    //
	JOYKEY_LB,    //
	JOYKEY_RB,    //
	JOYKEY_LT,    //
	JOYKEY_RT,    //
	JOYKEY_A,     //
	JOYKEY_B,     //
	JOYKEY_X,     //
	JOYKEY_Y,     //
	JOYKEY_MAX
}JOYKEY;

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

#endif