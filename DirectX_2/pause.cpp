//==============================================================
//
//SHOOTING GAME[pause.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"pause.h"
#include"game.h"
#include"player.h"
#include"input.h"
#include"fade.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_aVtxBuffPause = NULL;//頂点バッファへのポインタ
PAUSE_MENU g_pauseMenu;                        //ポーズメニュー
int g_nPause;

//==============================================================
//ポーズの初期化処理
//==============================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\000.png",
		&g_pTexturePause);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_aVtxBuffPause,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_aVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

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

	//頂点バッファをアンロックする
	g_aVtxBuffPause->Unlock();
}

//==============================================================
//ポーズの終了処理
//==============================================================
void UninitPause(void)
{
	//テクスチャの破棄
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	//頂点バッファの破棄
	if (g_aVtxBuffPause != NULL)
	{
		g_aVtxBuffPause->Release();
		g_aVtxBuffPause = NULL;
	}
}

//==============================================================
//ポーズの更新処理
//==============================================================
void UpdatePause(void)
{
	/*VERTEX_2D* pVtx;

	//頂点バッファをロックし,頂点データへのポインタを取得
	g_aVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx += 4;//頂点データのポインタを4つ分進める

	//頂点バッファをアンロックする
	g_aVtxBuffPause->Unlock();*/

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//決定キー(ENTERキー)が押された
		//メニューにあわせてモードの切り替え
		/*if (GetKeyboardTrigger(DIK_1) == true)
		{
		}
		else if (GetKeyboardTrigger(DIK_2) == true)
		{
			SetFade(MODE_GAME);
		}
		else if (GetKeyboardTrigger(DIK_3) == true)
		{
			SetFade(MODE_TITLE);
		}*/


	}
}

//==============================================================
//ポーズの描画処理
//==============================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPause;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_aVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause);

	for (nCntPause = 0; nCntPause < 8; nCntPause++)
	{
		if (g_nPause == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * 8,
				2);
		}
	}
}