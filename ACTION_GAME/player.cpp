//==============================================================
//
//ACTION_GAME[player.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"block.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//頂点バッファのポインタ
int g_nCounterAnimPlayer;                       //アニメーションカウンター
int g_nPatternAnimPlayer;                       //アニメーションパターンNo.
float g_fLengthPlayer;                          //対角線の長さ
float g_fAnglePlayer;                           //対角線の角度
Player g_player;                                //プレイヤーの情報

//==============================================================
//プレイヤーの初期化処理
//==============================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice, 
		"data\\TEXTURE\\player000.png", 
		&g_pTexturePlayer);

	g_nCounterAnimPlayer = 0;                                                     //カウンターを初期化する
	g_nPatternAnimPlayer = 0;                                                     //パターンNo.を初期化する
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT - 50.0f, 0.0f);//位置を初期化する(初期位置)
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                                //移動量を初期化する
	g_player.posOld = D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT - 50.0f, 0.0f);
	g_player.state = {};
	g_player.nCounterState = {};
	g_player.bJump = {};
	g_player.bRightMove = {};
	g_player.pBlock = NULL;

	//対角線の長さを算出する
	g_fLengthPlayer = sqrtf(100.0f * 100.0f + 150.0f * 150.0f) / 2.0f;

	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(200.0f, 300.0f);

	g_player.bDisp = true;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer, 
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x - 50.0f;
	pVtx[0].pos.y = g_player.pos.y - 150.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + 50.0f;
	pVtx[1].pos.y = g_player.pos.y - 150.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x - 50.0f;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + 50.0f;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================
//プレイヤーの終了処理
//==============================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//==============================================================
//プレイヤーの更新処理
//==============================================================
void UpdatePlayer(void)
{
	g_nCounterAnimPlayer++;//カウンターを計算
	VERTEX_2D* pVtx{};     //頂点情報へのポインタ

	if (g_player.bDisp == true)
	{
		//左に移動する
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT) == true)
		{//Aキーが押された
			g_player.move.x -= 1.0f;

			//アニメーション
			if ((g_nCounterAnimPlayer % 7 == 0) && g_player.bJump == false)
			{
				g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;//パターンNo.を更新する

				//頂点バッファをロックし,頂点情報へのポインタを取得
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 1.0f);
			}
		}
		//右に移動する
		else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) == true)
		{//Dキーが押された
			g_player.move.x += 1.0f;

			//アニメーション
			if ((g_nCounterAnimPlayer % 7 == 0) && g_player.bJump == false)
			{
				g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;//パターンNo.を更新する

				//頂点バッファをロックし,頂点情報へのポインタを取得
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.5f);
			}
		}
		//ブロックとの左右の当たり判定
		CollisionBlockX(&g_player.pos, &g_player.posOld, &g_player.move, 100.0f, 150.0f);
		//ブロックとの上下の当たり判定
		if (CollisionBlockY(&g_player.pos, &g_player.posOld, &g_player.move, 100.0f, 150.0f) == true)
		{
			g_player.bJump = false;
		}
		////自由落下時にジャンプをできなくする
		//if (g_player.move.y == true )
		//{
		//	g_player.bJump = true;
		//}
		//ジャンプする
		if ((GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_UP) == true) && g_player.bJump == false/* && g_player.move.y == false*/)
		{
			g_player.move.y = -21.0f;
			g_player.bJump = true;
		}
		//ブロックを出す
		/*if ((GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) == true) && g_player.bJump == false)
		{//Sキーが押された
			SetBlock(D3DXVECTOR3(g_player.pos.x + 75.0f, g_player.pos.y - 50.0f, 0.0f));
		}*/
		if (GetKeyboardTrigger(DIK_Q) == true && g_player.bJump == false)
		{//Qキーが押された
			SetBlock(D3DXVECTOR3(g_player.pos.x - 75.0f, g_player.pos.y - 50.0f, 0.0f));
		}
		if (GetKeyboardTrigger(DIK_E) == true && g_player.bJump == false)
		{//Eキーが押された
			SetBlock(D3DXVECTOR3(g_player.pos.x + 75.0f, g_player.pos.y - 50.0f, 0.0f));
		}

		//前回の位置を保存
		g_player.posOld = g_player.pos;

		//if (g_player.pBlock != NULL)
		//{//ブロックに乗っている
		//	g_player.pBlock
		//}

		//位置を更新
		g_player.pos.x += g_player.move.x;//横移動
		g_player.pos.y += g_player.move.y;//落下

		g_player.move.y += 0.98f;         //重力加算

		////最終的には消す(床)
		//if (g_player.pos.y >= SCREEN_HEIGHT)
		//{
		//	g_player.pos.y = SCREEN_HEIGHT;
		//	g_player.move.y = 0.0f;
		//	g_player.bJump = false;
		//	//g_player.bDisp = false;
		//}

		//移動量を更新(減衰させる)
		g_player.move.x += (0.0f - g_player.move.x) * 0.25f;

		//頂点バッファをロックし,頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos.x = g_player.pos.x - 50.0f;
		pVtx[0].pos.y = g_player.pos.y - 150.0f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_player.pos.x + 50.0f;
		pVtx[1].pos.y = g_player.pos.y - 150.0f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_player.pos.x - 50.0f;
		pVtx[2].pos.y = g_player.pos.y;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_player.pos.x + 50.0f;
		pVtx[3].pos.y = g_player.pos.y;
		pVtx[3].pos.z = 0.0f;

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
}

//==============================================================
//プレイヤーの描画処理
//==============================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//==============================================================
//プレイヤーのヒット処理
//==============================================================
void HitPlayer(int nDamage)
{

}

//==============================================================
//プレイヤーの取得処理
//==============================================================
Player* GetPlayer(void)
{
	return &g_player;
}