//==============================================================
//
//[bullet.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"bullet.h"
#include"player.h"
#include"shadow.h"
#include"explosion.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];                   //バレット情報

//==============================================================
//バレットの初期化処理
//==============================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//バレットの情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].nType = {};
		g_aBullet[nCntBullet].mtxWorld = {};
		g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-7.5f, 7.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(7.5f, 7.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-7.5f, -7.5f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(7.5f, -7.5f, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//==============================================================
//バレットの終了処理
//==============================================================
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//==============================================================
//バレットの更新処理
//==============================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_3D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//弾の位置の更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//寿命のカウントダウン
			g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//爆発の設定
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				g_aBullet[nCntBullet].bUse = false;//使用してない状態にする
				ShadowEX(g_aBullet[nCntBullet].nIdxShadow);
			}

			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//==============================================================
//バレットの描画処理
//==============================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//計算用のマトリックス
			D3DXMATRIX mtxTrans, mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			//カメラの逆行列を設定
			g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBullet,
				2);
		}
	}

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//==============================================================
//バレットの設定処理
//==============================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 dir, int nLife)
{
	int nCntBullet;
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].dir = dir;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].nIdxShadow = SetShadow(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			g_aBullet[nCntBullet].bUse = true;//使用している状態にする

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}