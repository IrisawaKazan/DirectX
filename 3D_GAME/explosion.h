//==============================================================
//
//3D_GAME[explosion.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"main.h"
#include"bullet.h"
#include"player.h"

//マクロ定義
#define MAX_EXPLOSION (MAX_BULLET)//爆発の最大数

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 col;    //色
	D3DXVECTOR3 move;   //移動量
	int nCounterAnim;   //アニメーションカウンター
	int nPatternAnim;   //アニメーションパターンNo.
	bool bUse;          //使用しているかどうか
	D3DXMATRIX mtxWorld;//ワールドマトリックス
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif