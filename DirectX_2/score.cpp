//==============================================================
//
//SHOOTING GAME[score.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"score.h"
#include"main.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//頂点バッファのポインタ
D3DXVECTOR3 g_posScore;                        //スコアの位置
int g_nScore;                                  //スコアの値

//==============================================================
//スコアの初期化処理
//==============================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, 
		"data\\TEXTURE\\number100.png", 
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置を初期化する
	g_nScore = 0;                              //値を初期化する

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, 
		&g_pVtxBuffScore, 
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//スコアの終了処理
//==============================================================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//==============================================================
//スコアの更新処理
//==============================================================
void UpdateScore(void)
{
	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	pVtx += 4;//頂点データのポインタを4つ分進める

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//スコアの描画処理
//==============================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		if (g_nScore == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				4 * 8, 
				2);
		}
	}
}

//==============================================================
//スコアの設定処理
//==============================================================
void SetScore(int nScore)
{
	int aPosTexU[8];//各桁の数字を格納
	g_nScore = nScore;

	int nCntScore;

	aPosTexU[0] = g_nScore;
	aPosTexU[1] = g_nScore;
	aPosTexU[2] = g_nScore;
	aPosTexU[3] = g_nScore;
	aPosTexU[4] = g_nScore;
	aPosTexU[5] = g_nScore;
	aPosTexU[6] = g_nScore;
	aPosTexU[7] = g_nScore;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//スコアの加算処理
//==============================================================
void AddScore(int nValue)
{
	int aPosTexU[8];//各桁の数字を格納
	g_nScore += nValue;

	int nCntScore;

	aPosTexU[0] = g_nScore;
	aPosTexU[1] = g_nScore;
	aPosTexU[2] = g_nScore;
	aPosTexU[3] = g_nScore;
	aPosTexU[4] = g_nScore;
	aPosTexU[5] = g_nScore;
	aPosTexU[6] = g_nScore;
	aPosTexU[7] = g_nScore;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//スコアの取得処理
//==============================================================
int GetScore(void)
{
	return g_nScore;
}