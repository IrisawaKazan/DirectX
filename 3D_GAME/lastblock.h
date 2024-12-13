//==============================================================
//
//3D_GAME[lastblock.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _LASTBLOCK_H_
#define _LASTBLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//マクロ定義
#define MAX_LBLOCK (128)
#define MAX_MLBLOCK (1.0f)

//ラストブロックの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;      //位置
	D3DXVECTOR3 rot;      //向き
	D3DXVECTOR3 move;     //移動量
	D3DXVECTOR3 vtxMin;   //モデルの最小値
	D3DXVECTOR3 vtxMax;   //モデルの最大値
	LPD3DXMESH pMesh;     //メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルへのポインタ
	DWORD dwNumMat;       //マテリアルの数
	D3DXMATRIX mtxWorld;  //ワールドマトリックス
	bool bUse;            //使っているかいないか
	int nType;            //種類
}LastBlock;

//プロトタイプ宣言
void InitLastBlock(void);
void UninitLastBlock(void);
void UpdateLastBlock(void);
void DrawLastBlock(void);
void SetLastBlock(D3DXVECTOR3 pos, int type);
void CollisionLastBlockX(void);//X軸の当たり判定
LastBlock* GetLastBlock(void);

#endif