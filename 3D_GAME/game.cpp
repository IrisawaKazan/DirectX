//==============================================================
//
//3D_GAME[game.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"game.h"

//グローバル変数宣言
bool g_bPause = false;  //ポーズ中かどうか
STAGE g_stage = STAGE_1;//現在のモード

//==============================================================
//ゲーム画面の初期化処理
//==============================================================
void InitGame(void)
{
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

	case STAGE_4:
		InitStage4();
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
	if (GetKeyboardTrigger(DIK_TAB) || GetKeyboardTrigger(DIK_LSHIFT) == true)
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

		case STAGE_4:
			UpdateStage4();
			break;
		}
	}
}

//==============================================================
//ゲーム画面の描画処理
//==============================================================
void DrawGame(void)
{
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

	case STAGE_4:
		DrawStage4();
		break;
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