//==============================================================
//
//ACTION_GAME[block.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;    //���
	float fWidth; //��
	float fHeight;//����
	bool bUse;
}Block;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos);
void CollisionBlockX(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);
bool CollisionBlockY(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);

#endif