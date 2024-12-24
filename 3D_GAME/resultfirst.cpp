//==============================================================
//
//3D_GAME[resultfirst.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"resultfirst.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureResultFirst = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultFirst = NULL;//頂点バッファのポインタ

//==============================================================
//リザルト画面の初期化処理
//==============================================================
void InitResultFirst(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\result100.png",//ステージクリアの絵と,エンターで次のステージ,スペースでタイトルへみたいな画像に
		&g_pTextureResultFirst);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultFirst,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffResultFirst->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResultFirst->Unlock();
}

//==============================================================
//リザルト画面の終了処理
//==============================================================
void UninitResultFirst(void)
{
	//テクスチャの破棄
	if (g_pTextureResultFirst != NULL)
	{
		g_pTextureResultFirst->Release();
		g_pTextureResultFirst = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultFirst != NULL)
	{
		g_pVtxBuffResultFirst->Release();
		g_pVtxBuffResultFirst = NULL;
	}
}

//==============================================================
//リザルト画面の更新処理
//==============================================================
void UpdateResultFirst(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) == true && GetFade() == FADE_NONE)
	{
		SetTitle(TITLE_2);
		//モード設定(タイトル画面に移行)
		SetFade(MODE_TITLE);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetStage(STAGE_2);
		SetTitle(TITLE_2);
		//次のステージに移行
		SetFade(MODE_GAME);
	}
}

//==============================================================
//リザルト画面の描画処理
//==============================================================
void DrawResultFirst(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultFirst, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultFirst);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}