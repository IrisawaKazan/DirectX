//==============================================================
//
//[stage2.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"stage2.h"

//==============================================================
//ゲーム画面の初期化処理
//==============================================================
void InitStage2(void)
{
	InitCamera();
	InitLight();
	InitShadow();
	InitPlayer();
	InitMeshfield();
	InitWall();
	InitDeadBlock();
	InitDeadBlockHS();
	InitGoalBlock();
	InitLastBlock();
	InitMeshwall();
	InitGoal();

	//ゴール
	SetGoal(D3DXVECTOR3(0.0f, GOAL_HEIGHT, 150.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//デッドブロック
	{
		//動かない
		SetDeadBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		//→
		SetDeadBlock(D3DXVECTOR3(-120.0f, 0.0f, -120.0f), 1);
		SetDeadBlock(D3DXVECTOR3(-80.0f, 0.0f, -80.0f), 1);
		//←
		SetDeadBlock(D3DXVECTOR3(200.0f, 0.0f, -120.0f), 2);
		//↑
		SetDeadBlock(D3DXVECTOR3(-80.0f, 0.0f, -400.0f), 3);
		SetDeadBlock(D3DXVECTOR3(40.0f, 0.0f, -650.0f), 3);
		SetDeadBlock(D3DXVECTOR3(80.0f, 0.0f, -690.0f), 3);
		SetDeadBlock(D3DXVECTOR3(120.0f, 0.0f, -730.0f), 3);
		//↓
		SetDeadBlock(D3DXVECTOR3(-120.0f, 0.0f, 250.0f), 4);
		SetDeadBlock(D3DXVECTOR3(120.0f, 0.0f, 250.0f), 4);
		SetDeadBlock(D3DXVECTOR3(-120.0f, 0.0f, 550.0f), 4);
		SetDeadBlock(D3DXVECTOR3(-80.0f, 0.0f, 590.0f), 4);
	}

	//ハイスピードデッドブロック
	{
		//→
		SetDeadBlockHS(D3DXVECTOR3(-400.0f, 0.0f, -40.0f), 1);
		SetDeadBlockHS(D3DXVECTOR3(-600.0f, 0.0f, -40.0f), 1);
		SetDeadBlockHS(D3DXVECTOR3(-800.0f, 0.0f, 120.0f), 1);
		//←
		SetDeadBlockHS(D3DXVECTOR3(900.0f, 0.0f, 80.0f), 2);
		//↑
		SetDeadBlockHS(D3DXVECTOR3(-40.0f, 0.0f, -800.0f), 3);
		//↓

		//→→
		SetDeadBlockHS(D3DXVECTOR3(-1200.0f, 0.0f, 0.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2000.0f, 0.0f, 40.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2000.0f, 0.0f, 80.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2000.0f, 0.0f, 120.0f), 5);
		//←←
		SetDeadBlockHS(D3DXVECTOR3(1500.0f, 0.0f, 0.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(2600.0f, 0.0f, 40.0f), 6);
		//↑↑
		SetDeadBlockHS(D3DXVECTOR3(-80.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(-40.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(40.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(80.0f, 0.0f, -800.0f), 7);
		//↓↓

		//→↑
		//SetDeadBlockHS(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);
		//→↓
		//SetDeadBlockHS(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 11);
		//←↑
		//SetDeadBlockHS(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 12);
		//←↓
		//SetDeadBlockHS(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 13);
	}

	//ゴールブロック↑
	{
		SetGoalBlock(D3DXVECTOR3(-160.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(-120.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(-80.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(-40.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(0.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(40.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(80.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(120.0f, 0.0f, MAX_GBLOCKPOS), 2);
		SetGoalBlock(D3DXVECTOR3(160.0f, 0.0f, MAX_GBLOCKPOS), 2);
	}

	//ラストブロック
	{
		//→
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, -120.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, -80.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, -40.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 0.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 40.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 80.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 120.0f), 1);
		//←
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 120.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 80.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 40.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 0.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, -40.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, -80.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, -120.0f), 2);
		//↑
		SetLastBlock(D3DXVECTOR3(120.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(80.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(40.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(0.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(-40.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(-80.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(-120.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		//↓
		SetLastBlock(D3DXVECTOR3(-120.0f, 0.0f, MAX_LBLOCKPOSS2), 4);
		SetLastBlock(D3DXVECTOR3(-80.0f, 0.0f, MAX_LBLOCKPOSS2), 4);
		SetLastBlock(D3DXVECTOR3(-40.0f, 0.0f, MAX_LBLOCKPOSS2), 4);
		SetLastBlock(D3DXVECTOR3(0.0f, 0.0f, MAX_LBLOCKPOSS2), 4);
		SetLastBlock(D3DXVECTOR3(40.0f, 0.0f, MAX_LBLOCKPOSS2), 4);
		SetLastBlock(D3DXVECTOR3(80.0f, 0.0f, MAX_LBLOCKPOSS2), 4);
		SetLastBlock(D3DXVECTOR3(120.0f, 0.0f, MAX_LBLOCKPOSS2), 4);
	}
}

//==============================================================
//ゲーム画面の終了処理
//==============================================================
void UninitStage2(void)
{
	UninitCamera();
	UninitLight();
	UninitPlayer();
	UninitMeshfield();
	UninitShadow();
	UninitWall();
	UninitDeadBlock();
	UninitDeadBlockHS();
	UninitGoalBlock();
	UninitLastBlock();
	UninitMeshwall();
	UninitGoal();
}

//==============================================================
//ゲーム画面の更新処理
//==============================================================
void UpdateStage2(void)
{
	Player* pPlayer = GetPlayer();

	UpdateCamera();
	UpdateLight();
	UpdatePlayer();
	UpdateMeshfield();
	UpdateShadow();
	UpdateWall();
	UpdateDeadBlock();
	UpdateDeadBlockHS();
	UpdateGoalBlock();
	UpdateLastBlock();
	UpdateMeshwall();
	UpdateGoal();

	if (pPlayer->pos.z <= -150.0f && GetFade() == FADE_NONE)
	{//ゲームオーバー
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x <= -150.0f && GetFade() == FADE_NONE)
	{//ゲームオーバー
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x >= 150.0f && GetFade() == FADE_NONE)
	{//ゲームオーバー
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.z >= 140.0f && GetFade() == FADE_NONE)
	{//クリア
		//モード設定(  画面に移行)
		SetFade(MODE_CLEAR);
	}
}

//==============================================================
//ゲーム画面の描画処理
//==============================================================
void DrawStage2(void)
{
	SetCamera();

	DrawPlayer();
	DrawMeshfield();
	DrawGoal();
	DrawDeadBlock();
	DrawDeadBlockHS();
	DrawGoalBlock();
	DrawLastBlock();
	DrawWall();
	DrawMeshwall();
	DrawShadow();
}