//==============================================================
//
//[input.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP = 0,//十字キー(上)
	JOYKEY_DOWN,  //十字キー(下)
	JOYKEY_LEFT,  //十字キー(左)
	JOYKEY_RIGHT, //十字キー(右)
	JOYKEY_START, //
	JOYKEY_BACK,  //
	JOYKEY_L3,    //Lスティック
	JOYKEY_R3,    //Rスティック
	JOYKEY_LB,    //
	JOYKEY_RB,    //
	JOYKEY_LT,    //
	JOYKEY_RT,    //
	JOYKEY_A,     //Aボタン
	JOYKEY_B,     //Bボタン
	JOYKEY_X,     //Xボタン
	JOYKEY_Y,     //Yボタン
	JOYKEY_MAX
}JOYKEY;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

#endif