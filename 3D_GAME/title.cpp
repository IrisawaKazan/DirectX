//==============================================================
//
//3D_GAME[title.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"title.h"

//グローバル変数宣言
TITLE g_title = TITLE_1;//現在のモード

//==============================================================
//タイトル画面の初期化処理
//==============================================================
void InitTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		InitTitlefirst();
		break;

	case TITLE_2:
		InitTitlesecond();
		break;

	case TITLE_3:
		InitTitlethird();
		break;
	}
}

//==============================================================
//タイトル画面の終了処理
//==============================================================
void UninitTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		UninitTitlefirst();
		break;
	}
}

//==============================================================
//タイトル画面の更新処理
//==============================================================
void UpdateTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		UpdateTitlefirst();
		break;

	case TITLE_2:
		UpdateTitlesecond();
		break;

	case TITLE_3:
		UpdateTitlethird();
		break;
	}
}

//==============================================================
//タイトル画面の描画処理
//==============================================================
void DrawTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		DrawTitlefirst();
		break;

	case TITLE_2:
		DrawTitlesecond();
		break;

	case TITLE_3:
		DrawTitlethird();
		break;
	}
}

//==============================================================
//タイトルの設定
//==============================================================
void SetTitle(TITLE title)
{
	g_title = title;
}

//==============================================================
//タイトルの取得
//==============================================================
TITLE GetTitle(void)
{
	return g_title;
}