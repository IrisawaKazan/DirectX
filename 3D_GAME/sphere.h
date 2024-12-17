//==============================================================
//
//3D_GAME[sphere.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include"main.h"

//スフィアの構造体
typedef struct
{
	LPD3DXMESH pMesh;     //メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルへのポインタ
	DWORD dwNumMat;       //マテリアルの数
	int nIdxModelParant;  //親モデルのインデックス
	D3DXVECTOR3 pos;      //位置(オフセット)
	D3DXVECTOR3 rot;      //向き
	D3DXMATRIX mtxWorld;  //ワールドマトリックス
}Sphere;

//プロトタイプ宣言
void InitSphere(void);
void UninitSphere(void);
void UpdateSphere(void);
void DrawSphere(void);

#endif