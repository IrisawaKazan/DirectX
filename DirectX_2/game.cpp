//==============================================================
//
//SHOOTING GAME[game.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"game.h"
#include"player.h"
#include"bullet.h"
#include"explosion.h"
#include"input.h"
#include"score.h"
#include"background.h"
#include"enemy.h"
#include"pause.h"
#include"fade.h"

//グローバル変数宣言
bool g_bPause = false;//ポーズ中かどうか

//==============================================================
//ゲーム画面の初期化処理
//==============================================================
void InitGame(void)
{
	InitBackground();

	InitPlayer();

	InitBullet();

	InitExplosion();

	InitEnemy();

	SetEnemy(D3DXVECTOR3(900.0f, 25.0f, 0.0f), D3DXVECTOR3(-1.0f, 2.5f, 0.0f), 1);

	SetEnemy(D3DXVECTOR3(950.0f, 25.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f, 200.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1075.0f, 300.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1075.0f, 400.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f, 500.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f, 700.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(900.0f, 700.0f, 0.0f), D3DXVECTOR3(-1.0f, -2.5f, 0.0f), 1);

	SetEnemy(D3DXVECTOR3(500.0f, 500.0f, 0.0f), D3DXVECTOR3(2.5f, -2.0f, 0.0f), 2);


	SetEnemy(D3DXVECTOR3(1100.0f * 2.5f, 25.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 2.5f, 100.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 2.5f, 200.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f * 2.5f, 300.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f * 2.5f, 400.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 2.5f, 500.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 2.5f, 600.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1100.0f * 2.5f, 700.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(150.0f, -500.0f, 0.0f), D3DXVECTOR3(2.5f, 2.0f, 0.0f), 2);


	SetEnemy(D3DXVECTOR3(900.0f * 3.5f, 25.0f, 0.0f), D3DXVECTOR3(-1.0f, 2.5f, 0.0f), 1);

	SetEnemy(D3DXVECTOR3(1100.0f * 3.5f, 25.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 3.5f, 100.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 3.5f, 200.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f * 3.5f, 300.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f * 3.5f, 400.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 3.5f, 500.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 3.5f, 600.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1100.0f * 3.5f, 700.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);


	SetEnemy(D3DXVECTOR3(950.0f * 4.5f, 25.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 4.5f, 100.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 4.5f, 200.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1075.0f * 4.5f, 300.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1075.0f * 4.5f, 400.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 4.5f, 500.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 4.5f, 600.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f * 4.5f, 700.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);


	SetEnemy(D3DXVECTOR3(1100.0f * 5.5f, 25.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 5.5f, 100.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 5.5f, 200.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f * 5.5f, 300.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(950.0f * 5.5f, 400.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1000.0f * 5.5f, 500.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1050.0f * 5.5f, 600.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);

	SetEnemy(D3DXVECTOR3(1100.0f * 5.5f, 700.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);


	SetEnemy(D3DXVECTOR3(950.0f * 6.0f, 300.0f, 0.0f), D3DXVECTOR3(-3.5f, 0.2f, 0.0f), 1);

	SetEnemy(D3DXVECTOR3(950.0f * 6.0f, 400.0f, 0.0f), D3DXVECTOR3(-3.5f, -0.2f, 0.0f), 1);


	SetEnemy(D3DXVECTOR3(950.0f * 3.0f, 300.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.2f, 0.0f), 1);

	SetEnemy(D3DXVECTOR3(950.0f * 3.0f, 400.0f, 0.0f), D3DXVECTOR3(-1.0f, -0.2f, 0.0f), 1);

	/*for (int nCount = 0; nCount <= MAX_ENEMY; nCount++)
	{
		SetEnemy(D3DXVECTOR3(, rand(), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	}*/

	/*for (int nCountSetEnemy = 0; nCountSetEnemy = 3; nCountSetEnemy++)
	{
		SetEnemy(D3DXVECTOR3(350.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), nCountSetEnemy);
	}*/

	InitScore();

	g_bPause = false;//ポーズ解除
}

//==============================================================
//ゲーム画面の終了処理
//==============================================================
void UninitGame(void)
{
	UninitBackground();

	UninitPlayer();

	UninitBullet();

	UninitExplosion();

	UninitEnemy();

	UninitScore();
}

//==============================================================
//ゲーム画面の更新処理
//==============================================================
void UpdateGame(void)
{
	Player pPlayer;
	Enemy pEnemy;

	if (GetKeyboardTrigger(DIK_TAB) == true)
	{//ポーズキーが押された
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{//ポーズ中
		//ポーズの更新処理
		UpdatePause();
	}

	if (g_bPause == false)
	{//ポーズ中でなければ
		UpdateBackground();

		UpdatePlayer();

		UpdateBullet();

		UpdateExplosion();

		UpdateEnemy();

		UpdateScore();

		/*if (pPlayer.bDisp == true && GetFade() == FADE_NONE)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RESULT);
		}*/

		/*if (pEnemy.bUse == false && GetFade() == FADE_NONE)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RESULT);
		}*/

		if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
		{//決定キー(ENTERキー)が押された
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RESULT);
		}
	}
}

//==============================================================
//ゲーム画面の描画処理
//==============================================================
void DrawGame(void)
{
	DrawBackground();

	DrawPlayer();

	DrawBullet();

	DrawExplosion();

	DrawEnemy();

	DrawScore();

	if (g_bPause == true)
	{//ポーズ中
		//ポーズの描画処理
		DrawPause();
	}
}

//==============================================================
//ポーズの有効無効設定
//==============================================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}