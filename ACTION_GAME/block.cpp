//==============================================================
//
//ACTION_GAME[block.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"block.h"

//マクロ定義
#define MAX_BLOCK (/*128*/61)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;//頂点バッファのポインタ
Block g_aBlock[MAX_BLOCK];                     //ブロックの情報

//==============================================================
//ブロックの初期化処理
//==============================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block200.png",
		&g_pTextureBlock);

	//ブロックの情報の初期化
	for (nCntBlock = 0 ; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;   //使用していない状態にする
		g_aBlock[nCntBlock].fWidth = 25.0f; //使用していない状態にする
		g_aBlock[nCntBlock].fHeight = 50.0f;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
		pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
		pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
		pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
		pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
		pVtx[3].pos.z = 0.0f;

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
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//ブロックの終了処理
//==============================================================
void UninitBlock(void)
{
	//テクスチャの破棄
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//==============================================================
//ブロックの更新処理
//==============================================================
void UpdateBlock(void)
{
	int nCntBlock;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[3].pos.z = 0.0f;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//ブロックの描画処理
//==============================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBlock);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックの使用されている
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				4 * nCntBlock, 
				2);
		}
	}
}

//==============================================================
//ブロックの設定処理
//==============================================================
void SetBlock(D3DXVECTOR3 pos)
{
	int nCntBlock;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//ブロックの使用されていない
			g_aBlock[nCntBlock].pos = pos;

			//頂点座標の設定
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[3].pos.z = 0.0f;

			g_aBlock[nCntBlock].bUse = true;//使用している状態にする

			break;
		}

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//ブロックの衝突処理 X
//==============================================================
void CollisionBlockX(D3DXVECTOR3* pPos,//現在の位置
	D3DXVECTOR3* pPosOld,              //前回の位置
	D3DXVECTOR3* pMove,                //移動量
	float fWidth,                      //幅
	float fHeight)                     //高さ
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//ブロックの左右の当たり判定
			if (pPosOld->y > g_aBlock[nCntBlock].pos.y &&
				pPosOld->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{
				//ブロックの左から右への当たり判定
				if (pPosOld->x + fWidth / 2.0f <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2.0f &&
					pPos->x + fWidth / 2.0f > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2.0f)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - fWidth / 2.0f - g_aBlock[nCntBlock].fWidth / 2.0f;
					pMove->x = 0.0f;
				}
				//ブロックの右から左への当たり判定
				if (pPosOld->x - fWidth / 2.0f >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2.0f &&
					pPos->x - fWidth / 2.0f < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2.0f)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x + fWidth / 2.0f + g_aBlock[nCntBlock].fWidth / 2.0f;
					pMove->x = 0.0f;
				}
			}
		}
	}
}

//==============================================================
//ブロックの衝突処理 Y
//==============================================================
bool CollisionBlockY(D3DXVECTOR3* pPos,//現在の位置
	D3DXVECTOR3* pPosOld,              //前回の位置
	D3DXVECTOR3* pMove,                //移動量
	float fWidth,                      //幅
	float fHeight)                     //高さ
{
	bool bLanding = false;//着地しているかどうか

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//ブロックの上下の当たり判定
			if (pPos->x + fWidth / 2.0f > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2.0f &&
				pPos->x - fWidth / 2.0f < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2.0f)
			{
				//ブロックの上から下への当たり判定
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y &&
					pPos->y > g_aBlock[nCntBlock].pos.y)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;
				}
				//ブロックの下から上への当たり判定
				else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight;
					pMove->y = 0.0f;
				}
			}
		}
	}
	return bLanding;
}