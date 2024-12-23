//==============================================================
//
//3D_GAME[deadblock.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _DEADBLOCK_H_
#define _DEADBLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"
#include"explosion.h"

//マクロ定義
#define MAX_DEADBLOCK (256)
#define MAX_MDBLOCK (1.5f)

//デッドブロックの構造体の定義
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
}DeadBlock;

//プロトタイプ宣言
void InitDeadBlock(void);
void UninitDeadBlock(void);
void UpdateDeadBlock(void);
void DrawDeadBlock(void);
void SetDeadBlock(D3DXVECTOR3 pos, int type);
void CollisionDeadBlockX(void);//X軸の当たり判定
DeadBlock* GetDeadBlock(void);

#endif