//==============================================================
//
//3D_GAME[meshwall.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include"main.h"

//マクロ定義
#define MAX_MWX (2)                                                           //横(X)の四角の数
#define MAX_MWZ (2)                                                           //縦(Z)の四角の数
#define MAX_MWPVTX ((MAX_MWX + 1) * (MAX_MWZ + 1))                            //頂点数
#define MAX_MWPOLYGON (MAX_MWX * MAX_MWZ * 2 + (MAX_MWZ - 1) * 2 * MAX_MWZ)   //ポリゴン数
#define MAX_MWPIDX ((MAX_MWX + 1) * 2 * MAX_MWZ + (MAX_MWZ - 1) * 2 * MAX_MWZ)//インデックス数
#define NUM_PLUS (/*80*/0.0f)
#define MAX_MWPOSX (150.0f + NUM_PLUS)                                        //壁のx
#define MAX_MWPOSZ (MAX_MWPOSX - NUM_PLUS)                                    //壁のz
#define MAX_MWHEIGHT (700.0f)                                                 //壁の高さ

//メッシュウォールの構造体の定義
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;     //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff; //インデックスバッファへのポインタ
	D3DXVECTOR3 pos;                 //位置
	D3DXVECTOR3 rot;                 //向き
	D3DXMATRIX mtxWorld;             //ワールドマトリックス
}Meshwall;

//プロトタイプ宣言
void InitMeshwall(void);
void UninitMeshwall(void);
void UpdateMeshwall(void);
void DrawMeshwall(void);

#endif