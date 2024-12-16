//==============================================================
//
//SHOOTING GAME[bullet.cpp]
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

//マクロ定義
#define MAX_BULLET (128)//弾の最大数

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move;//移動量
	int nLife;       //寿命
	BULLETTYPE type; //種類
	bool bUse;       //使用しているかどうか
}Bullet;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//頂点バッファのポインタ
Bullet g_aBullet[MAX_BULLET];                   //弾の情報

//==============================================================
//弾の初期化処理
//==============================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//弾の情報の初期化
	for (nCntBullet = 0 ; nCntBullet < MAX_BULLET ; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
		g_aBullet[nCntBullet].type = {};
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();
}

//==============================================================
//弾の終了処理
//==============================================================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//==============================================================
//弾の更新処理
//==============================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用される
			Enemy* pEnemy;//敵の情報へのポインタ
			int nCntEnemy;

			Player* pPlayer;
			int nCntPlayer;

			//敵の取得
			pEnemy = GetEnemy();

			pPlayer = GetPlayer();

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{//敵が使用されている
						if (g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + 40.0f/*右*/
							&& g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - 40.0f/*左*/
							&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - 55.0f/*上*/
							&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + 55.0f/*下*/)
						{
							//爆発の設定
							SetExplosion(pEnemy->pos, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

							pEnemy->bUse = false;              //敵を使用している状態にする
							g_aBullet[nCntBullet].bUse = false;//敵を使用している状態にする
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				for (nCntPlayer = 0; nCntPlayer < 1; nCntPlayer++, pPlayer++)
				{
					if (pPlayer->bDisp == true)
					{//使用されている
						if (g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + 40.0f/*右*/
							&& g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - 40.0f/*左*/
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - 40.0f/*上*/
							&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + 40.0f/*下*/)
						{
							//爆発の設定
							SetExplosion(pPlayer->pos, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

							pPlayer->bDisp = false;            //使用している状態にする
							g_aBullet[nCntBullet].bUse = false;//使用している状態にする
						}
					}
				}
			}

			//弾の位置の更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);				

			if (g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 25)
			{
				g_aBullet[nCntBullet].bUse = false;//使用してない状態にする
			}

			//寿命のカウントダウン
			g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].nLife < 0)
			{
				//爆発の設定
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

				g_aBullet[nCntBullet].bUse = false;//使用してない状態にする
			}

			/*if (g_aBullet[nCntBullet].type == 0)
			{
				float fRotMove, fRotDest, fRotDiff;
				fRotMove = atan2f(g_aBullet->pos.y, g_aBullet->pos.x);
				fRotDest = atan2f(pEnemy->pos.y, pEnemy->pos.x);
				fRotDiff = fRotDest - fRotMove;//目標の移動方向までの角度

				//角度の値を修正する
				
				
				fRotMove += fRotDiff * 0.2f;//移動方向の速度
			
				//角度の値を修正する
				

				g_aBullet[nCntBullet].move.x = sinf(fRotMove) * 3;
				g_aBullet[nCntBullet].move.y = cosf(fRotMove) * 3;
			}*/
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//==============================================================
//弾の描画処理
//==============================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				4 * nCntBullet, 
				2);
		}
	}
}

//==============================================================
//弾の設定処理
//==============================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCntBullet].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 300;
			g_aBullet[nCntBullet].bUse = true;//使用している状態にする
			g_aBullet[nCntBullet].type = type;

			break;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}