//==============================================================
//
//SHOOTING GAME[enemy.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"

//マクロ定義
#define MAX_ENEMY (128)//敵の最大数

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;
	int nType;      //種類
	bool bUse;      //使用しているかどうか
	int nLife;
	int g_shotcounter;
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type);
Enemy* GetEnemy(void);

#endif