//==============================================================
//
//[shadow.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include"main.h"
#include"bullet.h"
#include"player.h"

//マクロ定義
#define MAX_SHADOW (1 + MAX_BULLET)

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void ShadowEX(int nIdxShadow);

#endif