//==============================================================
//
//3D_GAME[meshfield.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include"main.h"

//マクロ定義
#define MAX_MFX (2)                                                           //横(X)の四角の数
#define MAX_MFZ (2)                                                           //縦(Z)の四角の数
#define MAX_MFPVTX ((MAX_MFX + 1) * (MAX_MFZ + 1))                            //頂点数
#define MAX_MFPOLYGON (MAX_MFX * MAX_MFZ * 2 + (MAX_MFZ - 1) * 2 * MAX_MFZ)   //ポリゴン数
#define MAX_MFPIDX ((MAX_MFX + 1) * 2 * MAX_MFZ + (MAX_MFZ - 1) * 2 * MAX_MFZ)//インデックス数
#define MAX_MFPOS (150.0f)                                                    //四角一つの大きさ

//メッシュフィールドの構造体の定義
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;     //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff; //インデックスバッファへのポインタ
	D3DXVECTOR3 pos;                 //位置
	D3DXVECTOR3 rot;                 //向き
	D3DXMATRIX mtxWorld;             //ワールドマトリックス
}Meshfield;

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif