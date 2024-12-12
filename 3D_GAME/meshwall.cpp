//==============================================================
//
//[meshwall.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"meshwall.h"

//グローバル変数
Meshwall g_meshwall;

//==============================================================
//メッシュウォールの初期化処理
//==============================================================
void InitMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_meshwall.pTexture = NULL;
	g_meshwall.pVtxBuff = NULL;
	g_meshwall.pIdxBuff = NULL;
	g_meshwall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshwall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshwall.mtxWorld = {};

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_meshwall.pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MWPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_meshwall.pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MWPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshwall.pIdxBuff,
		NULL);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_meshwall.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = -D3DXVECTOR3(-MAX_MWPOSX, MAX_MWHEIGHT, MAX_MWPOSZ);
	pVtx[1].pos = -D3DXVECTOR3(0.0f, MAX_MWHEIGHT, MAX_MWPOSZ);
	pVtx[2].pos = -D3DXVECTOR3(MAX_MWPOSX, MAX_MWHEIGHT, MAX_MWPOSZ);
	pVtx[3].pos = -D3DXVECTOR3(-MAX_MWPOSX, MAX_MWHEIGHT / 2.0f, MAX_MWPOSZ);
	pVtx[4].pos = -D3DXVECTOR3(0.0f, MAX_MWHEIGHT / 2.0f, MAX_MWPOSZ);
	pVtx[5].pos = -D3DXVECTOR3(MAX_MWPOSX, MAX_MWHEIGHT / 2.0f, MAX_MWPOSZ);
	pVtx[6].pos = -D3DXVECTOR3(-MAX_MWPOSX, 0.0f, MAX_MWPOSZ);
	pVtx[7].pos = -D3DXVECTOR3(0.0f, 0.0f, MAX_MWPOSZ);
	pVtx[8].pos = -D3DXVECTOR3(MAX_MWPOSX, 0.0f, MAX_MWPOSZ);

	for (int nCntMeshwall = 0; nCntMeshwall < MAX_MWPVTX; nCntMeshwall++)
	{
		//各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
		pVtx[nCntMeshwall].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[nCntMeshwall].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
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
	g_meshwall.pVtxBuff->Unlock();

	//インデックスバッファの生成・インデックス情報の設定
	WORD* pIdx;

	//インデックスバッファをロック
	g_meshwall.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

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
	g_meshwall.pIdxBuff->Unlock();
}

//==============================================================
//メッシュウォールの終了処理
//==============================================================
void UninitMeshwall(void)
{
	if (g_meshwall.pTexture != NULL)
	{
		g_meshwall.pTexture->Release();
		g_meshwall.pTexture = NULL;
	}

	//頂点バッファの解放
	if (g_meshwall.pVtxBuff != NULL)
	{
		g_meshwall.pVtxBuff->Release();
		g_meshwall.pVtxBuff = NULL;
	}

	//インデックスバッファの解放
	if (g_meshwall.pIdxBuff != NULL)
	{
		g_meshwall.pIdxBuff->Release();
		g_meshwall.pIdxBuff = NULL;
	}
}

//==============================================================
//メッシュウォールの更新処理
//==============================================================
void UpdateMeshwall(void)
{

}

//==============================================================
//メッシュウォールの描画処理
//==============================================================
void DrawMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshwall.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshwall.rot.y, g_meshwall.rot.x, g_meshwall.rot.z);
	D3DXMatrixMultiply(&g_meshwall.mtxWorld, &g_meshwall.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_meshwall.pos.x, g_meshwall.pos.y, g_meshwall.pos.z);
	D3DXMatrixMultiply(&g_meshwall.mtxWorld, &g_meshwall.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_meshwall.mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_meshwall.pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_meshwall.pIdxBuff);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_meshwall.pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MWPVTX, 0, MAX_MWPOLYGON);
}