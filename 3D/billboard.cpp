//コピー用
//==============================================================
//
//[billboard.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"billboard.h"
#include"player.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;//頂点バッファへのポインタ
Billboard g_aBillboard[MAX_BILLBOARD];             //ビルボード情報

//==============================================================
//ビルボードの初期化処理
//==============================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBillboard;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wood.png",
		&g_pTextureBillboard);

	//ビルボードの情報の初期化
	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aBillboard[nCntBillboard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aBillboard[nCntBillboard].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aBillboard[nCntBillboard].nLife = 100;
		//g_aBillboard[nCntBillboard].nType = {};
		g_aBillboard[nCntBillboard].mtxWorld = {};
		g_aBillboard[nCntBillboard].bUse = false;//使用していない状態にする
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-75.0f, 75.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(75.0f, 75.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-75.0f, -75.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(75.0f, -75.0f, 0.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

	g_pVtxBuffBillboard->Unlock();
}

//==============================================================
//ビルボードの終了処理
//==============================================================
void UninitBillboard(void)
{
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//==============================================================
//ビルボードの更新処理
//==============================================================
void UpdateBillboard(void)
{
	//int nCntBillboard;
	//VERTEX_3D* pVtx;

	////頂点バッファをロックし,頂点データへのポインタを取得
	//g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	//{
	//	//弾の位置の更新
	//	g_aBillboard[nCntBillboard].pos += g_aBillboard[nCntBillboard].move;

	//	//頂点座標の更新
	//	pVtx[0].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);

	//	if (g_aBillboard[nCntBillboard].pos.x > SCREEN_WIDTH + 25)
	//	{
	//		g_aBillboard[nCntBillboard].bUse = false;//使用してない状態にする
	//	}

	//	//寿命のカウントダウン
	//	g_aBillboard[nCntBillboard].nLife--;

	//	pVtx += 4;//頂点データのポインタを4つ分進める
	//}

	////頂点バッファをアンロックする
	//g_pVtxBuffBillboard->Unlock();
}

//==============================================================
//ビルボードの描画処理
//==============================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			//計算用のマトリックス
			D3DXMATRIX mtxTrans, mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

			//カメラの逆行列を設定
			g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillboard);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBillboard,
				2);
		}
	}

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==============================================================
//ビルボードの設定処理
//==============================================================
void SetBillboard(D3DXVECTOR3 pos/*, D3DXVECTOR3 move, D3DXVECTOR3 dir, int nLife*/)
{
	int nCntBillboard;
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{//弾が使用されていない
			g_aBillboard[nCntBillboard].pos = pos;
			//g_aBillboard[nCntBillboard].move = move;
			//g_aBillboard[nCntBillboard].dir = dir;
			//g_aBillboard[nCntBillboard].nLife = 300;

			g_aBillboard[nCntBillboard].bUse = true;//使用している状態にする

			//頂点座標の設定
			//pVtx[0].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);

			break;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}