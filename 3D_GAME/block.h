//==============================================================
//
//[block.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//マクロ定義
#define MAX_BLOCK (128)

//ブロックの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;      //位置
	D3DXVECTOR3 rot;      //向き
	D3DXVECTOR3 vtxMin;   //モデルの最小値
	D3DXVECTOR3 vtxMax;   //モデルの最大値
	LPD3DXMESH pMesh;     //メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルへのポインタ
	DWORD dwNumMat;       //マテリアルの数
	D3DXMATRIX mtxWorld;  //ワールドマトリックス
	bool bUse;            //使っているかいないか
}Block;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos);
void CollisionBlockX(void);//X軸の当たり判定
void CollisionBlockZ(void);//Z軸の当たり判定

#endif