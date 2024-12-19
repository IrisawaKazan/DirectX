//==============================================================
//
//3D_GAME[result.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include"main.h"
#include"input.h"
#include"fade.h"
#include"game.h"
#include"title.h"
#include"resultfirst.h"
#include"resultsecond.h"
#include"resultthird.h"

//リザルトの種類
typedef enum
{
	RESULT_1 = 0,
	RESULT_2,
	RESULT_3,
	RESULT_MAX
}RESULT;

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(RESULT result);
RESULT GetResult(void);

#endif