//==============================================================
//
//[deadblockhighspeed.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _DEADBLOCKHS_H_
#define _DEADBLOCKHS_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//マクロ定義
#define MAX_DEADHSBLOCK (256)
#define MAX_MDHSBLOCK (3.0f)

//ハイスピードデッドブロックの構造体の定義
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
}DeadBlockHS;

//プロトタイプ宣言
void InitDeadBlockHS(void);
void UninitDeadBlockHS(void);
void UpdateDeadBlockHS(void);
void DrawDeadBlockHS(void);
void SetDeadBlockHS(D3DXVECTOR3 pos, int type);
void CollisionDeadBlockHSX(void);//X軸の当たり判定
DeadBlockHS* GetDeadBlockHS(void);

#endif