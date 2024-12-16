//==============================================================
//
//[meshhole.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"meshhole.h"

//グローバル変数
Meshhole g_meshhole;

//==============================================================
//メッシュホールの初期化処理
//==============================================================
void InitMeshhole(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_meshhole.pTexture = NULL;
	g_meshhole.pVtxBuff = NULL;
	g_meshhole.pIdxBuff = NULL;
	g_meshhole.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshhole.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshhole.mtxWorld = {};

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\",
		&g_meshhole.pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MHPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_meshhole.pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MHPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshhole.pIdxBuff,
		NULL);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_meshhole.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-MAX_MHPOS / 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[1].pos = D3DXVECTOR3(-MAX_MHPOS, MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[2].pos = D3DXVECTOR3(-MAX_MHPOS, -MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[3].pos = D3DXVECTOR3(-MAX_MHPOS / 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[4].pos = D3DXVECTOR3(MAX_MHPOS / 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[5].pos = D3DXVECTOR3(MAX_MHPOS, -MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[6].pos = D3DXVECTOR3(MAX_MHPOS, MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[7].pos = D3DXVECTOR3(MAX_MHPOS / 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[8].pos = D3DXVECTOR3(-MAX_MHPOS / 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[9].pos = D3DXVECTOR3(-MAX_MHPOS, MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[10].pos = D3DXVECTOR3(-MAX_MHPOS * 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[11].pos = D3DXVECTOR3(-MAX_MHPOS * 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[12].pos = D3DXVECTOR3(-MAX_MHPOS, -MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[13].pos = D3DXVECTOR3(MAX_MHPOS, -MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[14].pos = D3DXVECTOR3(MAX_MHPOS * 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[15].pos = D3DXVECTOR3(MAX_MHPOS * 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[16].pos = D3DXVECTOR3(MAX_MHPOS, MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[17].pos = D3DXVECTOR3(-MAX_MHPOS, MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);

	for (int nCntMeshwall = 0; nCntMeshwall < MAX_MHPVTX; nCntMeshwall++)
	{
		//各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
		pVtx[nCntMeshwall].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[nCntMeshwall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / 8.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f / 8.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(3.0f / 8.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(4.0f / 8.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(5.0f / 8.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(6.0f / 8.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(7.0f / 8.0f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(1.0f / 8.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(2.0f / 8.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(3.0f / 8.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(4.0f / 8.0f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(5.0f / 8.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(6.0f / 8.0f, 1.0f);
	pVtx[16].tex = D3DXVECTOR2(7.0f / 8.0f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_meshhole.pVtxBuff->Unlock();

	//インデックスバッファの生成・インデックス情報の設定
	WORD* pIdx;

	//インデックスバッファをロック
	g_meshhole.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

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
	g_meshhole.pIdxBuff->Unlock();
}

//==============================================================
//メッシュウォールの終了処理
//==============================================================
void UninitMeshhole(void)
{
	if (g_meshhole.pTexture != NULL)
	{
		g_meshhole.pTexture->Release();
		g_meshhole.pTexture = NULL;
	}

	//頂点バッファの解放
	if (g_meshhole.pVtxBuff != NULL)
	{
		g_meshhole.pVtxBuff->Release();
		g_meshhole.pVtxBuff = NULL;
	}

	//インデックスバッファの解放
	if (g_meshhole.pIdxBuff != NULL)
	{
		g_meshhole.pIdxBuff->Release();
		g_meshhole.pIdxBuff = NULL;
	}
}

//==============================================================
//メッシュウォールの更新処理
//==============================================================
void UpdateMeshhole(void)
{

}

//==============================================================
//メッシュウォールの描画処理
//==============================================================
void DrawMeshhole(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshhole.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshhole.rot.y, g_meshhole.rot.x, g_meshhole.rot.z);
	D3DXMatrixMultiply(&g_meshhole.mtxWorld, &g_meshhole.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_meshhole.pos.x, g_meshhole.pos.y, g_meshhole.pos.z);
	D3DXMatrixMultiply(&g_meshhole.mtxWorld, &g_meshhole.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_meshhole.mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_meshhole.pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_meshhole.pIdxBuff);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_meshhole.pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MHPVTX, 0, MAX_MHPOLYGON);
}