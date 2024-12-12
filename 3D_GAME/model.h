//==============================================================
//
//[model.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include"main.h"

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;     //メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルへのポインタ
	DWORD dwNumMat;       //マテリアルの数
	int nIdxModelParant;  //親モデルのインデックス
	D3DXVECTOR3 pos;      //位置(オフセット)
	D3DXVECTOR3 rot;      //向き
	D3DXMATRIX mtxWorld;  //ワールドマトリックス
}Model;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

#endif