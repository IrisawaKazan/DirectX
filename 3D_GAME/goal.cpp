//==============================================================
//
//[goal.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"goal.h"

//グローバル変数
Goal g_aGoal[MAX_GOAL];
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;//頂点バッファへのポインタ

//==============================================================
//ゴールの初期化処理
//==============================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntGoal;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\goal000.png",
		&g_pTextureGoal);

	//壁の情報の初期化
	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		g_aGoal[nCntGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGoal[nCntGoal].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGoal[nCntGoal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGoal[nCntGoal].mtxWorld = {};
		g_aGoal[nCntGoal].nType = {};
		g_aGoal[nCntGoal].bUse = false;//使用していない状態にする
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-GOAL_WIDTH, 0.0f, GOAL_HEIGHT);
		pVtx[1].pos = D3DXVECTOR3(GOAL_WIDTH, 0.0f, GOAL_HEIGHT);
		pVtx[2].pos = D3DXVECTOR3(-GOAL_WIDTH, 0.0f, -GOAL_HEIGHT);
		pVtx[3].pos = D3DXVECTOR3(GOAL_WIDTH, 0.0f, -GOAL_HEIGHT);

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
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//ゴールの終了処理
//==============================================================
void UninitGoal(void)
{
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//==============================================================
//ゴールの更新処理
//==============================================================
void UpdateGoal(void)
{

}

//==============================================================
//ゴールの描画処理
//==============================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_aGoal[nCntGoal].bUse == true)
		{
			//計算用のマトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aGoal[nCntGoal].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGoal[nCntGoal].rot.y, g_aGoal[nCntGoal].rot.x, g_aGoal[nCntGoal].rot.z);
			D3DXMatrixMultiply(&g_aGoal[nCntGoal].mtxWorld, &g_aGoal[nCntGoal].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aGoal[nCntGoal].pos.x, g_aGoal[nCntGoal].pos.y, g_aGoal[nCntGoal].pos.z);
			D3DXMatrixMultiply(&g_aGoal[nCntGoal].mtxWorld, &g_aGoal[nCntGoal].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aGoal[nCntGoal].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureGoal);

			//壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntGoal,
				2);
		}
	}
}

//==============================================================
//ゴールの設定処理
//==============================================================
int SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	int nCntGoal;
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_aGoal[nCntGoal].bUse == false)
		{
			g_aGoal[nCntGoal].pos = pos;
			g_aGoal[nCntGoal].rot = rot;
			g_aGoal[nCntGoal].col = col;

			g_aGoal[nCntGoal].bUse = true;

			//頂点カラー RGBA
			pVtx[0].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);
			pVtx[1].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);
			pVtx[2].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);
			pVtx[3].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);

			break;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();

	return nCntGoal;//壁の番号(index)を返す
}