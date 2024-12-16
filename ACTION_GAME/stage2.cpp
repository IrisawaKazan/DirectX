//==============================================================
//
//ACTION_GAME[stage2.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"stage1.h"
#include"stage2.h"
#include"game.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"pause.h"
#include"fade.h"

//==============================================================
//ゲーム画面の初期化処理
//==============================================================
void InitStage2(void)
{
	InitBackground();

	InitBlock();

	//SetBlock:56

	//床
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 25.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 125.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 175.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 225.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 275.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 325.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 375.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 425.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 525.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 575.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 625.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 675.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 725.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 825.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 875.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 925.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 975.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1025.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1125.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1175.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1225.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1275.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//床の段差
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 875.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 925.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 975.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1025.0f, SCREEN_HEIGHT - 50.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, SCREEN_HEIGHT - 50.0f, 0.0f));

	//壁
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 325.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 375.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 425.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 475.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 525.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 575.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 625.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 675.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 725.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 775.0f, 0.0f));
	//壁のでっぱり
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, SCREEN_HEIGHT - 425.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, SCREEN_HEIGHT - 475.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, SCREEN_HEIGHT - 525.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, SCREEN_HEIGHT - 575.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, SCREEN_HEIGHT - 625.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, SCREEN_HEIGHT - 675.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, SCREEN_HEIGHT - 725.0f, 0.0f));

	//壁2 - タイプ変える
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 225.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 325.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 375.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 425.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 475.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 525.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 575.0f, 0.0f));
	//壁2のつっぺ
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 125.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 125.0f, SCREEN_HEIGHT - 575.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 575.0f, 0.0f));

	InitPlayer();
}

//==============================================================
//ゲーム画面の終了処理
//==============================================================
void UninitStage2(void)
{
	UninitBackground();

	UninitBlock();

	UninitPlayer();
}

//==============================================================
//ゲーム画面の更新処理
//==============================================================
void UpdateStage2(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	UpdateBackground();

	UpdateBlock();

	UpdatePlayer();

	////if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	//{//決定キー(ENTERキー)が押された
	//	モード設定(リザルト画面に移行)
	//	SetFade(MODE_RESULT);
	//}
	if (pPlayer->pos.y >= SCREEN_HEIGHT + 150.0f && GetFade() == FADE_NONE)
	{//落ちたら画面を遷移する
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x <= -25.0f && GetFade() == FADE_NONE)
	{//画面の左に行ったら画面を遷移する
		pPlayer->bDisp = false;
		SetStage(STAGE_1);
		//モード設定
		SetFade(MODE_GAME);
	}
	if (pPlayer->pos.x >= SCREEN_WIDTH + 25.0f && GetFade() == FADE_NONE)
	{//画面の右に行ったら画面を遷移する
		pPlayer->bDisp = false;
		SetStage(STAGE_3);
		//次のステージに移行
		SetFade(MODE_GAME);
	}
	if ((pPlayer->pos.y <= 0.0f && pPlayer->pos.x <= SCREEN_WIDTH - 500.0f) && GetFade() == FADE_NONE)
	{//画面の左上に行ったら画面を遷移する
		pPlayer->bDisp = false;
		SetStage(STAGE_1);
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
}

//==============================================================
//ゲーム画面の描画処理
//==============================================================
void DrawStage2(void)
{
	DrawBackground();

	DrawBlock();

	DrawPlayer();
}