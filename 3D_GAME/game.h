//==============================================================
//
//3D_GAME[game.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _GAME_H_
#define _GAME_H_

#include"main.h"
#include"player.h"
#include"input.h"
#include"pause.h"
#include"fade.h"
#include"wall.h"
#include"light.h"
#include"polygon.h"
#include"meshfield.h"
#include"meshwall.h"
#include"billboard.h"
#include"explosion.h"
#include"deadblock.h"
#include"deadblockhighspeed.h"
#include"goalblock.h"
#include"lastblock.h"
#include"goal.h"
#include"stage1.h"
#include"stage2.h"
#include"stage3.h"
#include"stage4.h"
#include"sphere.h"
#include"model.h"
#include"result.h"

//マクロ定義
#define MAX_GBLOCKPOS (120.0f)
#define MAX_LBLOCKPOSS1 (750.0f)
#define MAX_LBLOCKPOSS2 (MAX_LBLOCKPOSS1 * 1.675f)
#define MAX_PPP (1800.0f)
#define MAX_PPP1 (2600.0f)
#define MAX_PPP2 (2300.0f)

//ステージの種類
typedef enum
{
	STAGE_1 = 0,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_MAX
}STAGE;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetEnablePause(bool bPause);
void SetStage(STAGE stage);
STAGE GetStage(void);

#endif