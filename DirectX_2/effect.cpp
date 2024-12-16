//==============================================================
//
//SHOOTING GAME[effect.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"effect.h"

//マクロ定義
#define MAX_EFFECT (4096)//エフェクトの最大数

//エフェクト構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;  //色
	float fRedius;  //半径(大きさ)
	int nLife;      //寿命
	bool bUse;      //使用しているかどうか
}Effect;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//頂点バッファのポインタ
Effect g_aEffect[MAX_EFFECT];                   //エフェクトの情報

//==============================================================
//エフェクトの初期化処理
//==============================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//エフェクトの情報の初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fRedius = 0.25;
		g_aEffect[nCntEffect].nLife = 100;
		g_aEffect[nCntEffect].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(50.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 60.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//==============================================================
//エフェクトの終了処理
//==============================================================
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//==============================================================
//エフェクトの更新処理
//==============================================================
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			Enemy* pEnemy;//敵の情報へのポインタ
			int nCntEnemy;

			//敵の取得
			pEnemy = GetEnemy();

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			{
				if (pEnemy->bUse == true)
				{//敵が使用されている
					//if (/*敵と弾が当たった*/)
					//{
					//	//爆発の設定
					//	SetExplosion(/*位置*/, /*色*/);

					//	pEnemy->bUse = false;              //敵を使用している状態にする
					//	g_aBullet[nCntBullet].bUse = false;//敵を使用している状態にする
					//}
				}
			}

			//g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].col;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);

			if (g_aEffect[nCntEffect].pos.x > SCREEN_WIDTH + 25)
			{
				g_aEffect[nCntEffect].bUse = false;//使用してない状態にする
			}

			//寿命のカウントダウン
			g_aEffect[nCntEffect].nLife--;

			if (g_aEffect[nCntEffect].nLife < 0)
			{
				//爆発の設定
				SetExplosion(g_aEffect[nCntEffect].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));

				g_aEffect[nCntEffect].bUse = false;//使用してない状態にする
			}
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//==============================================================
//エフェクトの描画処理
//==============================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEffect);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEffect,
				2);
		}
	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==============================================================
//エフェクトの設定処理
//==============================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife)
{
	int nCntEffect;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;

			/*//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);*/

			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRedius = fRedius;
			g_aEffect[nCntEffect].nLife = 300;
			g_aEffect[nCntEffect].bUse = true;//使用している状態にする

			break;
		}

		//pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}