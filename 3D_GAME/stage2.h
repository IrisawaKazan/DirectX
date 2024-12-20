//==============================================================
//
//3D_GAME[stage2.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _STAGE2_H_
#define _STAGE2_H_

#include"main.h"
#include"game.h"
#include"player.h"
#include"input.h"
#include"pause.h"
#include"fade.h"
#include"stage1.h"
#include"sound.h"
#include"clear.h"

#define MAX_PPP (1800.0f)
#define MAX_PPP1 (2600.0f)
#define MAX_PPP2 (2300.0f)

//プロトタイプ宣言
void InitStage2(void);
void UninitStage2(void);
void UpdateStage2(void);
void DrawStage2(void);

#endif