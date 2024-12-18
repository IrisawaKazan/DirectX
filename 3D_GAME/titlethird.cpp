//==============================================================
//
//3D_GAME[titlethird.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"titlethird.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTitlethird = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlethird = NULL;//頂点バッファのポインタ

//==============================================================
//タイトルサード画面の初期化処理
//==============================================================
void InitTitlethird(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\titlethird101.png",//豪華に
		&g_pTextureTitlethird);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlethird,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitlethird->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitlethird->Unlock();
}

//==============================================================
//タイトルサード画面の終了処理
//==============================================================
void UninitTitlethird(void)
{
	//テクスチャの破棄
	if (g_pTextureTitlethird != NULL)
	{
		g_pTextureTitlethird->Release();
		g_pTextureTitlethird = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitlethird != NULL)
	{
		g_pVtxBuffTitlethird->Release();
		g_pVtxBuffTitlethird = NULL;
	}
}

//==============================================================
//タイトルサード画面の更新処理
//==============================================================
void UpdateTitlethird(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{//決定キー(ENTERキー)が押された
		//モード設定(チュートリアル画面に移行)
		SetFade(MODE_TUTORIAL);
	}
	else if (GetKeyboardTrigger(DIK_2) == true && GetFade() == FADE_NONE)
	{//2が押された
		//モード設定(ゲーム画面に移行)
		SetStage(STAGE_2);
		SetFade(MODE_GAME);
	}
}

//==============================================================
//タイトルサード画面の描画処理
//==============================================================
void DrawTitlethird(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitlethird, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitlethird);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}