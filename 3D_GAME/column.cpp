//==============================================================
//
//[column.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"column.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureColumn = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffColumn = NULL;//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffColumn = NULL; //インデックスバッファへのポインタ
D3DXVECTOR3 g_posColumn;                        //位置
D3DXVECTOR3 g_rotColumn;                        //向き
D3DXMATRIX g_mtxWorldColumn;                    //ワールドマトリックス

//==============================================================
//円柱の初期化処理
//==============================================================
void InitColumn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.png",
		&g_pTextureColumn);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_CPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffColumn,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_CPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffColumn,
		NULL);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffColumn->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, MAX_CPOS, -MAX_CPOS);
	pVtx[1].pos = D3DXVECTOR3(MAX_CPOS / 2.0f, MAX_CPOS, -MAX_CPOS /2.0f);
	pVtx[2].pos = D3DXVECTOR3(MAX_CPOS, MAX_CPOS, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MAX_CPOS / 2.0f, MAX_CPOS, MAX_CPOS / 2.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, MAX_CPOS, MAX_CPOS);
	pVtx[5].pos = D3DXVECTOR3(-MAX_CPOS / 2.0f, MAX_CPOS, MAX_CPOS / 2.0f);
	pVtx[6].pos = D3DXVECTOR3(-MAX_CPOS, MAX_CPOS, 0.0f);

	for (int nCntColumn = 0; nCntColumn < MAX_CPVTX; nCntColumn++)
	{
		//各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
		pVtx[nCntColumn].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[nCntColumn].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);


	//頂点バッファをアンロックする
	g_pVtxBuffColumn->Unlock();

	//インデックスバッファの生成・インデックス情報の設定
	WORD* pIdx;

	//インデックスバッファをロック
	g_pIdxBuffColumn->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	pIdx[0] = 9;
	pIdx[1] = 0;
	pIdx[2] = 10;
	pIdx[3] = 1;
	pIdx[4] = 11;
	pIdx[5] = 2;
	pIdx[6] = 12;
	pIdx[7] = 3;
	pIdx[8] = 13;
	pIdx[9] = 4;
	pIdx[10] = 14;
	pIdx[11] = 5;
	pIdx[12] = 15;
	pIdx[13] = 6;
	pIdx[14] = 16;
	pIdx[15] = 7;
	pIdx[16] = 17;
	pIdx[17] = 8;

	//インデックスバッファのアンロック
	g_pIdxBuffColumn->Unlock();
}

//==============================================================
//円柱の終了処理
//==============================================================
void UninitColumn(void)
{
	if (g_pTextureColumn != NULL)
	{
		g_pTextureColumn->Release();
		g_pTextureColumn = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffColumn != NULL)
	{
		g_pVtxBuffColumn->Release();
		g_pVtxBuffColumn = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffColumn != NULL)
	{
		g_pIdxBuffColumn->Release();
		g_pIdxBuffColumn = NULL;
	}
}

//==============================================================
//円柱の更新処理
//==============================================================
void UpdateColumn(void)
{

}

//==============================================================
//円柱の描画処理
//==============================================================
void DrawColumn(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldColumn);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotColumn.y, g_rotColumn.x, g_rotColumn.z);
	D3DXMatrixMultiply(&g_mtxWorldColumn, &g_mtxWorldColumn, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posColumn.x, g_posColumn.y, g_posColumn.z);
	D3DXMatrixMultiply(&g_mtxWorldColumn, &g_mtxWorldColumn, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldColumn);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffColumn, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffColumn);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureColumn);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_CPVTX, 0, MAX_CPOLYGON);
}