//==============================================================
//
//[wall.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"wall.h"

//グローバル変数
Wall g_aWall[MAX_WALL];
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//頂点バッファへのポインタ

//==============================================================
//壁の初期化処理
//==============================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntWall;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTextureWall);

	//壁の情報の初期化
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].mtxWorld = {};
		g_aWall[nCntWall].nType = {};
		g_aWall[nCntWall].bUse = false;//使用していない状態にする
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH, 0.0f, WALL_HEIGHT);
		pVtx[1].pos = D3DXVECTOR3(WALL_WIDTH, 0.0f, WALL_HEIGHT);
		pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH, 0.0f, -WALL_HEIGHT);
		pVtx[3].pos = D3DXVECTOR3(WALL_WIDTH, 0.0f, -WALL_HEIGHT);

		//各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//==============================================================
//壁の終了処理
//==============================================================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//==============================================================
//壁の更新処理
//==============================================================
void UpdateWall(void)
{

}

//==============================================================
//壁の描画処理
//==============================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//計算用のマトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntWall,
				2);
		}
	}
}

//==============================================================
//壁の設定処理
//==============================================================
int SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	int nCntWall;
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].col = col;

			g_aWall[nCntWall].bUse = true;

			//頂点カラー RGBA
			pVtx[0].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);
			pVtx[1].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);
			pVtx[2].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);
			pVtx[3].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);

			break;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	return nCntWall;//壁の番号(index)を返す
}

//==============================================================
//壁の当たり判定処理
//==============================================================
void CollisionWall(void)
{
	Player* pPlayer = GetPlayer();


}