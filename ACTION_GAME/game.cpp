//==============================================================
//
//ACTION_GAME[game.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"game.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"pause.h"
#include"fade.h"
#include"stage1.h"
#include"stage2.h"
#include"stage3.h"

//グローバル変数宣言
bool g_bPause = false;  //ポーズ中かどうか
STAGE g_stage = STAGE_1;//現在のモード

//==============================================================
//ゲーム画面の初期化処理
//==============================================================
void InitGame(void)
{
	/*InitBackground();

	InitBlock();

	//左端の壁
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 225.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 325.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 375.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 425.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 475.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 525.0f, 0.0f));

	//天井


	//床
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 25.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 125.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 175.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 225.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 275.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 325.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 375.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 425.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 525.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 575.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 625.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 675.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 725.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 825.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 875.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 925.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 975.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1025.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1125.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1175.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1225.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1275.0f, SCREEN_HEIGHT - 25.0f, 0.0f));

	//段差1
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 450.0f - 50.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 450.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));

	//浮いているブロック1 - タイプ変える
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, SCREEN_HEIGHT - 240.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, SCREEN_HEIGHT - 240.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1125.0f, SCREEN_HEIGHT - 240.0f, 0.0f));

	//壁 - タイプ変える
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 225.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 175.0f, 0.0f));

	////動作確認用
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 150.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1100.0f, SCREEN_HEIGHT - 300.0f, 0.0f));

	InitPlayer();*/

	switch (g_stage)
	{
	case STAGE_1:
		InitStage1();
		break;

	case STAGE_2:
		InitStage2();
		break;

	case STAGE_3:
		InitStage3();
		break;
	}

	InitPause();

	g_bPause = false;//ポーズ解除
}

//==============================================================
//ゲーム画面の終了処理
//==============================================================
void UninitGame(void)
{
	/*UninitBackground();

	UninitBlock();

	UninitPlayer();*/

	switch (g_stage)
	{
	case STAGE_1:
		UninitStage1();
		break;
	}
}

//==============================================================
//ゲーム画面の更新処理
//==============================================================
void UpdateGame(void)
{
	/*Player* pPlayer;
	pPlayer = GetPlayer();
	
	UpdateBackground();

	UpdateBlock();

	UpdatePlayer();

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{//決定キー(ENTERキー)が押された
		//モード設定(リザルト画面に移行)
		SetFade(MODE_RESULT);
	}
	if (pPlayer->pos.y >= SCREEN_HEIGHT + 150.0f && GetFade() == FADE_NONE)
	{//落ちたら画面を遷移する
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x <= -25.0f && GetFade() == FADE_NONE)
	{//最初の画面の左に行ったら画面を遷移する
		pPlayer->bDisp = false;
		//モード設定(タイトル画面に移行)
		SetFade(MODE_TITLE);
	}
	if (pPlayer->pos.x >= SCREEN_WIDTH + 25.0f && GetFade() == FADE_NONE)
	{//最初の画面の右に行ったら画面を遷移する
		pPlayer->bDisp = false;
		//モード設定(  画面に移行)
		SetFade(MODE_CLEAR);
	}*/

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
		switch (g_stage)
		{
		case STAGE_1:
			UpdateStage1();
			break;

		case STAGE_2:
			UpdateStage2();
			break;

		case STAGE_3:
			UpdateStage3();
			break;
		}
	}
}

//==============================================================
//ゲーム画面の描画処理
//==============================================================
void DrawGame(void)
{
	/*/DrawBackground();

	DrawBlock();

	DrawPlayer();
	
	//描画処理
	DrawPause();*/

	//if (g_bPause == false)
	{//ポーズ中
		switch (g_stage)
		{
		case STAGE_1:
			DrawStage1();
			break;

		case STAGE_2:
			DrawStage2();
			break;

		case STAGE_3:
			DrawStage3();
			break;
		}
	}

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

//==============================================================
//ステージの設定
//==============================================================
void SetStage(STAGE stage)
{
	g_stage = stage;
}

//==============================================================
//ステージの取得
//==============================================================
STAGE GetStage(void)
{
	return g_stage;
}