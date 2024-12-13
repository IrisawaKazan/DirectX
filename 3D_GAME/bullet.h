//==============================================================
//
//3D_GAME[bullet.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

#define MAX_BULLET (32)

//バレットの構造体
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 rot;    //向き
	D3DXVECTOR3 move;   //移動量
	D3DXVECTOR3 dir;    //方向
	int nLife;          //寿命
	int nType;          //種類
	int nIdxShadow;     //影の番号
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	bool bUse;          //試用しているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 dir, int nLife);//弾などを出したいとき

#endif