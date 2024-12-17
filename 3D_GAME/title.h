//==============================================================
//
//3D_GAME[title.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"
#include"input.h"
#include"fade.h"
#include"titlefirst.h"
#include"titlesecond.h"

//タイトルの種類
typedef enum
{
	TITLE_1 = 0,
	TITLE_2,
	TITLE_MAX
}TITLE;

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(TITLE title);
TITLE GetTitle(void);

#endif