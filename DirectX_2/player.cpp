//==============================================================
//
//SHOOTING GAME[player.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"bullet.h"
#include"enemy.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//頂点バッファのポインタ
int g_nCounterAnimPlayer;                       //アニメーションカウンター
int g_nPatternAnimPlayer;                       //アニメーションパターンNo.
D3DXVECTOR3 g_movePlayer;                       //移動量
D3DXVECTOR3 g_rotPlayer;                        //向き
float g_fLengthPlayer;                          //対角線の長さ
float g_fAnglePlayer;                           //対角線の角度
Player g_player;                                //プレイヤーの情報
//VERTEX_2D g_aVertex[4];                         //頂点情報を格納

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

	//player000.png

	g_nCounterAnimPlayer = 0;                       //カウンターを初期化する
	g_nPatternAnimPlayer = 0;                       //パターンNo.を初期化する
	g_player.pos = D3DXVECTOR3(75.0f, 360.0f, 0.0f);//位置を初期化する(初期位置)
	g_movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //移動量を初期化する
	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //向きを初期化する

	//対角線の長さを算出する
	g_fLengthPlayer = sqrtf(200.0f * 200.0f + 300.0f * 300.0f) / 2.0f;

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
	pVtx[0].pos.x = g_player.pos.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	/*//頂点座標の設定
	g_aVertex[0].pos = D3DXVECTOR3(450.0f, 150.0f, 0.0f);
	g_aVertex[1].pos = D3DXVECTOR3(850.0f, 150.0f, 0.0f);
	g_aVertex[2].pos = D3DXVECTOR3(450.0f, 550.0f, 0.0f);
	g_aVertex[3].pos = D3DXVECTOR3(850.0f, 550.0f, 0.0f);

	//rhwの設定
	g_aVertex[0].rhw = 1.0f;
	g_aVertex[1].rhw = 1.0f;
	g_aVertex[2].rhw = 1.0f;
	g_aVertex[3].rhw = 1.0f;

	//頂点カラーの設定
	g_aVertex[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aVertex[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aVertex[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aVertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	/*g_aVertex[0].col = D3DCOLOR_RGBA(0, 255, 200, 255);
	g_aVertex[1].col = D3DCOLOR_RGBA(0, 255, 200, 255);
	g_aVertex[2].col = D3DCOLOR_RGBA(0, 255, 200, 255);*/

	/*//テクスチャ座標の設定
	g_aVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_aVertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_aVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_aVertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);*/
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
	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//Aキーが押された
			if (GetKeyboardPress(DIK_W) == true)
			{//AキーとWキーがが押された
				g_movePlayer.x += sinf(D3DX_PI * -0.75f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * -0.75f) * 0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//AキーとSキーがが押された
				g_movePlayer.x += sinf(D3DX_PI * -0.25f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * -0.25f) * 0.5f;
			}
			else
			{
				g_movePlayer.x -= 0.5f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dキーが押された
			if (GetKeyboardPress(DIK_W) == true)
			{//DキーとWキーがが押された
				g_movePlayer.x += sinf(D3DX_PI * 0.75f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * 0.75f) * 0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//DキーとSキーがが押された
				g_movePlayer.x += sinf(D3DX_PI * 0.25f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * 0.25f) * 0.5f;
			}
			else
			{
				g_movePlayer.x += 0.5f;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//Wキーが押された
			g_movePlayer.y -= 0.5f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//Sキーが押された
			g_movePlayer.y += 0.5f;
		}
		/*else if (GetKeyboardPress(DIK_Z) == true)
		{//Zキーが押された
			g_rotPlayer.z += 0.0375f;
		}
		else if (GetKeyboardPress(DIK_X) == true)
		{//Xキーが押された
			g_rotPlayer.z -= 0.0375f;
		}*/
		/*else if (GetKeyboardPress(DIK_E) == true)
		{//Eキーが押された
			g_fAnglePlayer += 0.0375f;
		}
		else if (GetKeyboardPress(DIK_R) == true)
		{//Rキーが押された
			g_fAnglePlayer -= 0.0375f;
		}*/
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{//SPACEキーが押された
			//弾の設定
			SetBullet(g_player.pos,
				D3DXVECTOR3(5.0f, 0.0f, 0.0f),//スピード(移動量)
				100,
				BULLETTYPE_PLAYER);
		}

		//g_nCounterAnimPlayer++;//カウンターを計算
		VERTEX_2D* pVtx{};       //頂点情報へのポインタ

		/*//アニメーション
		if (g_nCounterAnimPlayer % 15 == 0)
		{
			g_nCounterAnimPlayer = 0;                             //カウンターを初期値に戻す
			g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 1;//パターンNo.を更新する

			//頂点バッファをロックし,頂点情報へのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f + 0.125f, 1.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffPlayer->Unlock();
		}*/

		//位置を更新
		g_player.pos.x += g_movePlayer.x;
		g_player.pos.y += g_movePlayer.y;

		//移動量を更新(減衰させる)
		g_movePlayer.x += (0.0f - g_movePlayer.x) * 0.085f;
		g_movePlayer.y += (0.0f - g_movePlayer.y) * 0.085f;

		//頂点バッファをロックし,頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の更新
		pVtx[0].pos.x = g_player.pos.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_player.pos.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
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
		/*pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
			2,                                       //プリミティブ(ポリゴン)数
			&g_aVertex[0],                           //頂点情報の先頭デバイス
			sizeof(VERTEX_2D));                      //頂点情報構造体のサイズ*/
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