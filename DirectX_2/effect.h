//==============================================================
//
//SHOOTING GAME[effect.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife);

#endif