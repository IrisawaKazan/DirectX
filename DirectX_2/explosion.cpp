//==============================================================
//
//SHOOTING GAME[explosion.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"

//マクロ定義
#define MAX_EXPLOSION (128)//爆発の最大数

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 col; //色
	int nCounterAnim;//アニメーションカウンター
	int nPatternAnim;//アニメーションパターンNo.
	bool bUse;       //使用しているかどうか
}Explosion;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//頂点バッファのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];             //爆発の情報

//==============================================================
//爆発の初期化処理
//==============================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//爆発の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
	g_pVtxBuffExplosion->Unlock();
}

//==============================================================
//爆発の終了処理
//==============================================================
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//==============================================================
//爆発の更新処理
//==============================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//カウンタを進めて,パターンNo.を更新する
			g_aExplosion[nCntExplosion].nCounterAnim++;
			if (g_aExplosion[nCntExplosion].nCounterAnim % 15 == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
				{
					g_aExplosion[nCntExplosion].bUse = false;//使用していない状態にする
				}
			}

			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//==============================================================
//爆発の描画処理
//==============================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//弾が使用されている
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntExplosion,
				2);
		}
	}
}

//==============================================================
//爆発の設定処理
//==============================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	int nCntExplosion;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//爆発が使用されていない
			//爆発の情報の設定
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 25.0f, g_aExplosion[nCntExplosion].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 25.0f, g_aExplosion[nCntExplosion].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 25.0f, g_aExplosion[nCntExplosion].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 25.0f, g_aExplosion[nCntExplosion].pos.y + 25.0f, 0.0f);

			//頂点カラーの設定
			g_aExplosion[nCntExplosion].bUse = true;//使用している状態にする

			break;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}