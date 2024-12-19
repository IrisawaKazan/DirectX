//==============================================================
//
//3D_GAME[result.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"result.h"

//グローバル変数宣言
RESULT g_result = RESULT_1;//現在のモード

//==============================================================
//リザルト画面の初期化処理
//==============================================================
void InitResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		InitResultFirst();
		break;

	case RESULT_2:
		InitResultSecond();
		break;

	case RESULT_3:
		InitResultThird();
		break;
	}
}

//==============================================================
//リザルト画面の終了処理
//==============================================================
void UninitResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		UninitResultFirst();
		break;
	}
}

//==============================================================
//リザルト画面の更新処理
//==============================================================
void UpdateResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		UpdateResultFirst();
		break;

	case RESULT_2:
		UpdateResultSecond();
		break;

	case RESULT_3:
		UpdateResultThird();
		break;
	}
}

//==============================================================
//リザルト画面の描画処理
//==============================================================
void DrawResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		DrawResultFirst();
		break;

	case RESULT_2:
		DrawResultSecond();
		break;

	case RESULT_3:
		DrawResultThird();
		break;
	}
}

//==============================================================
//リザルト画面の設定
//==============================================================
void SetResult(RESULT result)
{
	g_result = result;
}

//==============================================================
//リザルト画面の取得
//==============================================================
RESULT GetResult(void)
{
	return g_result;
}