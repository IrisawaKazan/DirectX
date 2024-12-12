//==============================================================
//
//[wall.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"
#include"player.h"

//マクロ定義
#define MAX_WALL (128)
#define WALL_WIDTH (250.0f)
#define WALL_HEIGHT (100.0f)

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 rot;    //向き
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	int nType;
	bool bUse;
}Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
int SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);
void CollisionWall(void);

#endif