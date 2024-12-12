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

//�}�N����`
#define MAX_SHADOW (1 + MAX_BULLET)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void ShadowEX(int nIdxShadow);

#endif