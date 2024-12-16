//==============================================================
//
//3D_GAME[meshfield.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"meshfield.h"

//グローバル変数
Meshfield g_meshfield;

//==============================================================
//メッシュフィールドの初期化処理
//==============================================================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_meshfield.pTexture = NULL;
	g_meshfield.pVtxBuff = NULL;
	g_meshfield.pIdxBuff = NULL;
	g_meshfield.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshfield.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshfield.mtxWorld = {};

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field100.png",
		&g_meshfield.pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MFPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_meshfield.pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MFPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshfield.pIdxBuff,
		NULL);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_meshfield.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-MAX_MFPOS, 0.0f, MAX_MFPOS);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, MAX_MFPOS);
	pVtx[2].pos = D3DXVECTOR3(MAX_MFPOS, 0.0f, MAX_MFPOS);
	pVtx[3].pos = D3DXVECTOR3(-MAX_MFPOS, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(MAX_MFPOS, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-MAX_MFPOS, 0.0f, -MAX_MFPOS);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -MAX_MFPOS);
	pVtx[8].pos = D3DXVECTOR3(MAX_MFPOS, 0.0f, -MAX_MFPOS);

	for (int nCntMeshfield = 0; nCntMeshfield < MAX_MFPVTX; nCntMeshfield++)
	{
		//各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
		pVtx[nCntMeshfield].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[nCntMeshfield].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_meshfield.pVtxBuff->Unlock();

	//インデックスバッファの生成・インデックス情報の設定
	WORD* pIdx;

	//インデックスバッファをロック
	g_meshfield.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	//インデックスの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファのアンロック
	g_meshfield.pIdxBuff->Unlock();
}

//==============================================================
//メッシュフィールドの終了処理
//==============================================================
void UninitMeshfield(void)
{
	if (g_meshfield.pTexture != NULL)
	{
		g_meshfield.pTexture->Release();
		g_meshfield.pTexture = NULL;
	}

	//頂点バッファの解放
	if (g_meshfield.pVtxBuff != NULL)
	{
		g_meshfield.pVtxBuff->Release();
		g_meshfield.pVtxBuff = NULL;
	}

	//インデックスバッファの解放
	if (g_meshfield.pIdxBuff != NULL)
	{
		g_meshfield.pIdxBuff->Release();
		g_meshfield.pIdxBuff = NULL;
	}
}

//==============================================================
//メッシュフィールドの更新処理
//==============================================================
void UpdateMeshfield(void)
{

}

//==============================================================
//メッシュフィールドの描画処理
//==============================================================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshfield.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshfield.rot.y, g_meshfield.rot.x, g_meshfield.rot.z);
	D3DXMatrixMultiply(&g_meshfield.mtxWorld, &g_meshfield.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_meshfield.pos.x, g_meshfield.pos.y, g_meshfield.pos.z);
	D3DXMatrixMultiply(&g_meshfield.mtxWorld, &g_meshfield.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_meshfield.mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_meshfield.pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_meshfield.pIdxBuff);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_meshfield.pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MFPVTX, 0, MAX_MFPOLYGON);
}