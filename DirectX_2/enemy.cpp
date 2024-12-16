//==============================================================
//
//SHOOTING GAME[enemy.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"enemy.h"
#include"explosion.h"
#include"bullet.h"

//マクロ定義
#define NUM_ENEMY (4)//敵の種類

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];//敵の情報

//==============================================================
//敵の初期化処理
//==============================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ(敵の種類分)の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy000.png",
		&g_pTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy100.png",
		&g_pTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy200.png",
		&g_pTextureEnemy[2]);

	//敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;   //g_pTextureEnemy[0];
		g_aEnemy[nCntEnemy].bUse = false;//使用していない状態にする
		g_aEnemy[nCntEnemy].g_shotcounter = 0;
	}

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//敵の終了処理
//==============================================================
void UninitEnemy(void)
{
	//テクスチャ(敵の種類分)の破棄
	if (g_pTextureEnemy[0] != NULL)
	{
		g_pTextureEnemy[0]->Release();
		g_pTextureEnemy[0] = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//==============================================================
//敵の更新処理
//==============================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;

	Enemy* pEnemy{};
	
	//if ()
	//{
	//	pEnemy->move.x += -1.5f;
	//}

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//弾が使用される

			//弾の位置の更新
			//g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].pos;

			//頂点座標の更新
			//pVtx[0].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f + 0.125f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f + 0.125f, 1.0f);

			if (g_aEnemy[nCntEnemy].pos.x < 0 - 25)
			{
				g_aEnemy[nCntEnemy].bUse = false;//使用してない状態にする
			}

			if (g_aEnemy[nCntEnemy].nLife < 0)
			{
				//爆発の設定
				SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));

				g_aEnemy[nCntEnemy].bUse = false;//使用してない状態にする
			}

			g_aEnemy[nCntEnemy].g_shotcounter++;

			if (g_aEnemy[nCntEnemy].g_shotcounter >= rand())
			{
				//敵が弾を撃つ
				SetBullet(g_aEnemy[nCntEnemy].pos,
					D3DXVECTOR3(-4.5f, 0.0f, 0.0f),//スピード(移動量)
					100,
					BULLETTYPE_ENEMY);

				g_aEnemy[nCntEnemy].g_shotcounter = 0;
			}

			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);

		}
		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	/*Enemy pEnemy;

	pEnemy.move.x += 10.0f;
	pEnemy.move.y += 10.0f;*/

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//敵の描画処理
//==============================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEnemy,
				2);
		}
	}
}

//==============================================================
//敵の設定処理
//==============================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない
			//敵の情報を設定
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = type;
			g_aEnemy[nCntEnemy].nLife = 120;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);

			//頂点カラーの設定
			g_aEnemy[nCntEnemy].bUse = true;//使用している状態にする

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//敵の取得
//==============================================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}