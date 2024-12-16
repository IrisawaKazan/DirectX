//==============================================================
//
//[meshhole.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MESHHOLE_H_
#define _MESHHOLE_H_

#include"main.h"

//マクロ定義
#define MAX_MHX (8)                                                           //横(X)の四角の数
#define MAX_MHZ (1)                                                           //縦(Z)の四角の数
#define MAX_MHPVTX ((MAX_MHX + 1) * (MAX_MHZ + 1))                            //頂点数
#define MAX_MHPOLYGON (MAX_MHX * MAX_MHZ * 2 + (MAX_MHZ - 1) * 2 * MAX_MHZ)   //ポリゴン数
#define MAX_MHPIDX ((MAX_MHX + 1) * 2 * MAX_MHZ + (MAX_MHZ - 1) * 2 * MAX_MHZ)//インデックス数
#define MAX_MHPOS (10.0f)                                                     //幅
#define MAX_MHHEIGHT (50.0f)                                                  //高さ
#define MAX_MHZ (25.0f)                                                       //奥行

//メッシュホールの構造体の定義
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;     //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff; //インデックスバッファへのポインタ
	D3DXVECTOR3 pos;                 //位置
	D3DXVECTOR3 rot;                 //向き
	D3DXMATRIX mtxWorld;             //ワールドマトリックス
}Meshhole;

//プロトタイプ宣言
void InitMeshhole(void);
void UninitMeshhole(void);
void UpdateMeshhole(void);
void DrawMeshhole(void);

#endif