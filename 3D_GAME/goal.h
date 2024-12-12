//==============================================================
//
//[goal.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include"main.h"
#include"player.h"

//マクロ定義
#define MAX_GOAL (1)
#define GOAL_WIDTH (150.0f)
#define GOAL_HEIGHT (25.0f)

//ゴールの構造体
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 rot;    //向き
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	int nType;
	bool bUse;
}Goal;

//プロトタイプ宣言
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
int SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);

#endif