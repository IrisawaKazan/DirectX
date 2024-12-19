//==============================================================
//
//3D_GAME[billboard.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include"main.h"

#define MAX_BILLBOARD (128)

//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 rot;    //向き
	D3DXVECTOR3 move;   //移動量
	//D3DXVECTOR3 dir;    //方向
	//int nLife;          //寿命
	//int nType;          //種類
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	bool bUse;          //試用しているかどうか
}Billboard;

//プロトタイプ宣言
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos/*, D3DXVECTOR3 move, D3DXVECTOR3 dir, int nLife*/);//弾などを出したいとき

#endif