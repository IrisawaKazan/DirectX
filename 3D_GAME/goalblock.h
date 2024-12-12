//==============================================================
//
//[goalblock.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _GOALBLOCK_H_
#define _GOALBLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//マクロ定義
#define MAX_GBLOCK (128)
#define MAX_MGBLOCKS1 (0.1f)
#define MAX_MGBLOCKS2 (0.05f)

//ゴールブロックの構造体の定義
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
	int nType;
}GoalBlock;

//プロトタイプ宣言
void InitGoalBlock(void);
void UninitGoalBlock(void);
void UpdateGoalBlock(void);
void DrawGoalBlock(void);
void SetGoalBlock(D3DXVECTOR3 pos, int type);
void CollisionGoalBlockX(void);//X軸の当たり判定
GoalBlock* GetGoalBlock(void);

#endif