//==============================================================
//
//ACTION_GAME[block.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;    //種類
	float fWidth; //幅
	float fHeight;//高さ
	bool bUse;
}Block;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos);
void CollisionBlockX(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);
bool CollisionBlockY(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);

#endif