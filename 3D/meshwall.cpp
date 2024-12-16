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
	pVtx[0].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT, MAX_MWPOS);
	pVtx[1].pos = D3DXVECTOR3(0.0f, MAX_MWHEIGHT, MAX_MWPOS);
	pVtx[2].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT, MAX_MWPOS);
	pVtx[3].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT / 2.0f, MAX_MWPOS);
	pVtx[4].pos = D3DXVECTOR3(0.0f, MAX_MWHEIGHT / 2.0f, MAX_MWPOS - 37.5f);
	pVtx[5].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT / 2.0f, MAX_MWPOS);
	pVtx[6].pos = D3DXVECTOR3(-MAX_MWPOS, 0.0f, MAX_MWPOS);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, MAX_MWPOS);
	pVtx[8].pos = D3DXVECTOR3(MAX_MWPOS, 0.0f, MAX_MWPOS);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT, MAX_MWPOS);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, MAX_MWHEIGHT, MAX_MWPOS);
	//pVtx[2].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT, MAX_MWPOS);
	//pVtx[3].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT, -MAX_MWPOS);
	//pVtx[5].pos = D3DXVECTOR3(0.0f, MAX_MWHEIGHT, -MAX_MWPOS);
	//pVtx[6].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT, -MAX_MWPOS);
	//pVtx[7].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT, 0.0f);
	//pVtx[8].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT, MAX_MWPOS);
	//pVtx[9].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT / 2.0f, MAX_MWPOS);
	//pVtx[10].pos = D3DXVECTOR3(0.0f, MAX_MWHEIGHT / 2.0f, MAX_MWPOS);
	//pVtx[11].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT / 2.0f, MAX_MWPOS);
	//pVtx[12].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT / 2.0f, 0.0f);
	//pVtx[13].pos = D3DXVECTOR3(MAX_MWPOS, MAX_MWHEIGHT / 2.0f, -MAX_MWPOS);
	//pVtx[14].pos = D3DXVECTOR3(0.0f, MAX_MWHEIGHT / 2.0f, -MAX_MWPOS);
	//pVtx[15].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT / 2.0f, -MAX_MWPOS);
	//pVtx[16].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT / 2.0f, 0.0f);
	//pVtx[17].pos = D3DXVECTOR3(-MAX_MWPOS, MAX_MWHEIGHT / 2.0f, MAX_MWPOS);
	//pVtx[18].pos = D3DXVECTOR3(-MAX_MWPOS, 0.0f, MAX_MWPOS);
	//pVtx[19].pos = D3DXVECTOR3(0.0f, 0.0f, MAX_MWPOS);
	//pVtx[20].pos = D3DXVECTOR3(MAX_MWPOS, 0.0f, MAX_MWPOS);
	//pVtx[21].pos = D3DXVECTOR3(MAX_MWPOS, 0.0f, 0.0f);
	//pVtx[22].pos = D3DXVECTOR3(MAX_MWPOS, 0.0f, -MAX_MWPOS);
	//pVtx[23].pos = D3DXVECTOR3(0.0f, 0.0f, -MAX_MWPOS);
	//pVtx[24].pos = D3DXVECTOR3(-MAX_MWPOS, 0.0f, -MAX_MWPOS);
	//pVtx[25].pos = D3DXVECTOR3(-MAX_MWPOS, 0.0f, 0.0f);
	//pVtx[26].pos = D3DXVECTOR3(-MAX_MWPOS, 0.0f, MAX_MWPOS);

	for (int nCntMeshwall = 0; nCntMeshwall < MAX_MWPVTX; nCntMeshwall++)
	{
		//各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
		pVtx[nCntMeshwall].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[nCntMeshwall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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

	////テクスチャの座標設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f / 8.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(2.0f / 8.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(3.0f / 8.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(4.0f / 8.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(5.0f / 8.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(6.0f / 8.0f, 0.0f);
	//pVtx[7].tex = D3DXVECTOR2(7.0f / 8.0f, 0.0f);
	//pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[9].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[10].tex = D3DXVECTOR2(1.0f / 8.0f, 0.5f);
	//pVtx[11].tex = D3DXVECTOR2(2.0f / 8.0f, 0.5f);
	//pVtx[12].tex = D3DXVECTOR2(3.0f / 8.0f, 0.5f);
	//pVtx[13].tex = D3DXVECTOR2(4.0f / 8.0f, 0.5f);
	//pVtx[14].tex = D3DXVECTOR2(5.0f / 8.0f, 0.5f);
	//pVtx[15].tex = D3DXVECTOR2(6.0f / 8.0f, 0.5f);
	//pVtx[16].tex = D3DXVECTOR2(7.0f / 8.0f, 0.5f);
	//pVtx[17].tex = D3DXVECTOR2(1.0f, 0.5f);
	//pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[19].tex = D3DXVECTOR2(1.0f / 8.0f, 1.0f);
	//pVtx[20].tex = D3DXVECTOR2(2.0f / 8.0f, 1.0f);
	//pVtx[21].tex = D3DXVECTOR2(3.0f / 8.0f, 1.0f);
	//pVtx[22].tex = D3DXVECTOR2(4.0f / 8.0f, 1.0f);
	//pVtx[23].tex = D3DXVECTOR2(5.0f / 8.0f, 1.0f);
	//pVtx[24].tex = D3DXVECTOR2(6.0f / 8.0f, 1.0f);
	//pVtx[25].tex = D3DXVECTOR2(7.0f / 8.0f, 1.0f);
	//pVtx[26].tex = D3DXVECTOR2(1.0f, 1.0f);

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

	////インデックスの設定
	//pIdx[0] = 9;
	//pIdx[1] = 0;
	//pIdx[2] = 10;
	//pIdx[3] = 1;
	//pIdx[4] = 11;
	//pIdx[5] = 2;
	//pIdx[6] = 12;
	//pIdx[7] = 3;
	//pIdx[8] = 13;
	//pIdx[9] = 4;
	//pIdx[10] = 14;
	//pIdx[11] = 5;
	//pIdx[12] = 15;
	//pIdx[13] = 6;
	//pIdx[14] = 16;
	//pIdx[15] = 7;
	//pIdx[16] = 17;
	//pIdx[17] = 8;
	//pIdx[18] = 8;
	//pIdx[19] = 18;
	//pIdx[20] = 18;
	//pIdx[21] = 9;
	//pIdx[22] = 19;
	//pIdx[23] = 10;
	//pIdx[24] = 20;
	//pIdx[25] = 11;
	//pIdx[26] = 21;
	//pIdx[27] = 12;
	//pIdx[28] = 22;
	//pIdx[29] = 13;
	//pIdx[30] = 23;
	//pIdx[31] = 14;
	//pIdx[32] = 24;
	//pIdx[33] = 15;
	//pIdx[34] = 25;
	//pIdx[35] = 16;
	//pIdx[36] = 26;
	//pIdx[37] = 17;

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