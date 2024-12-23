//==============================================================
//
//3D_GAME[stage4.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"stage4.h"

//==============================================================
//ゲーム画面の初期化処理
//==============================================================
void InitStage4(void)
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
	InitSphere();
	InitBillboard();
	InitExplosion();
	//InitSound(HWND(-1));

	//ビルボード(雲)
	SetBillboard(D3DXVECTOR3(-200.0f, 80.0f, 200.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 80.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(-40.0f, -100.0f, -200.0f));

	SetBillboard(D3DXVECTOR3(-150.0f, 200.0f, -200.0f));
	SetBillboard(D3DXVECTOR3(0.0f, 200.0f, -200.0f));
	SetBillboard(D3DXVECTOR3(150.0f, 200.0f, -200.0f));

	//ゴール
	SetGoal(D3DXVECTOR3(0.0f, GOAL_HEIGHT, 150.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//デッドブロック
	{
		//動かない
		SetDeadBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		SetDeadBlock(D3DXVECTOR3(130.0f, 0.0f, 130.0f), 0);
		SetDeadBlock(D3DXVECTOR3(130.0f, 0.0f, -130.0f), 0);
		SetDeadBlock(D3DXVECTOR3(-130.0f, 0.0f, 130.0f), 0);
		SetDeadBlock(D3DXVECTOR3(-130.0f, 0.0f, -130.0f), 0);
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

		//↓

		//→→
		SetDeadBlockHS(D3DXVECTOR3(-1200.0f, 0.0f, 0.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2000.0f, 0.0f, 40.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2000.0f, 0.0f, 80.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2000.0f, 0.0f, 120.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2800.0f, 0.0f, -40.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2800.0f, 0.0f, -120.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-4200.0f, 0.0f, 40.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-4200.0f, 0.0f, 80.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-4200.0f, 0.0f, 120.0f), 5);
		//←←
		SetDeadBlockHS(D3DXVECTOR3(1500.0f, 0.0f, 0.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(2600.0f, 0.0f, 40.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(1800.0f, 0.0f, 40.0f), 6);

		SetDeadBlockHS(D3DXVECTOR3(5920.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(5960.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6000.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6040.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6080.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6120.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6160.0f, 0.0f, 120.0f), 6);
		//SetDeadBlockHS(D3DXVECTOR3(6200.0f, 0.0f, 120.0f), 6);
		//SetDeadBlockHS(D3DXVECTOR3(6240.0f, 0.0f, 120.0f), 6);
		//SetDeadBlockHS(D3DXVECTOR3(6280.0f, 0.0f, 120.0f), 6);
		//SetDeadBlockHS(D3DXVECTOR3(6320.0f, 0.0f, 120.0f), 6);
		//SetDeadBlockHS(D3DXVECTOR3(6360.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6400.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6440.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6480.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6520.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6560.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6600.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(6640.0f, 0.0f, 120.0f), 6);
		//↑↑
		SetDeadBlockHS(D3DXVECTOR3(-80.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(-40.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(40.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(80.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(-40.0f, 0.0f, -2000.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(-40.0f, 0.0f, -4250.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(-80.0f, 0.0f, -4250.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(-120.0f, 0.0f, -4250.0f), 7);
		//↓↓
		SetDeadBlockHS(D3DXVECTOR3(40.0f, 0.0f, 4000.0f), 8);
		SetDeadBlockHS(D3DXVECTOR3(80.0f, 0.0f, 4000.0f), 8);
		SetDeadBlockHS(D3DXVECTOR3(120.0f, 0.0f, 4000.0f), 8);
		//→↑
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP - 280.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP - 240.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP - 200.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP - 160.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP - 120.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP - 80.0f), 10);
		//SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP - 40.0f), 10);
		//SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP), 10);
		//SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP + 40.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP + 80.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP + 120.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP + 160.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP + 200.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP + 240.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP, 0.0f, -MAX_PPP + 280.0f), 10);

		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 - 280.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 - 240.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 - 200.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 - 160.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 - 120.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 - 80.0f), 10);
		//SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 - 40.0f), 10);
		//SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1), 10);
		//SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 + 40.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 + 80.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 + 120.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 + 160.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 + 200.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 + 240.0f), 10);
		SetDeadBlockHS(D3DXVECTOR3(-MAX_PPP1, 0.0f, -MAX_PPP1 + 280.0f), 10);
		//→↓

		//←↑
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 - 280.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 - 240.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 - 200.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 - 160.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 - 120.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 - 80.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 - 40.0f), 12);
		//SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 ), 12);
		//SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 + 40.0f), 12);
		//SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 + 80.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 + 120.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 + 160.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 + 200.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 + 240.0f), 12);
		SetDeadBlockHS(D3DXVECTOR3(MAX_PPP2, 0.0f, -MAX_PPP2 + 280.0f), 12);
		//←↓

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
void UninitStage4(void)
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
	UninitSphere();
	UninitBillboard();
	UninitExplosion();
	//UninitSound();
}

//==============================================================
//ゲーム画面の更新処理
//==============================================================
void UpdateStage4(void)
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
	UpdateSphere();
	UpdateBillboard();
	UpdateExplosion();

	if (pPlayer->pos.z <= -150.0f && GetFade() == FADE_NONE)
	{//ゲームオーバー
		SetExplosion(pPlayer->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x <= -150.0f && GetFade() == FADE_NONE)
	{//ゲームオーバー
		SetExplosion(pPlayer->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x >= 150.0f && GetFade() == FADE_NONE)
	{//ゲームオーバー
		SetExplosion(pPlayer->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pPlayer->bDisp = false;
		//モード設定(ゲームオーバー画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.z >= 142.0f && GetFade() == FADE_NONE)
	{//クリア
		SetClear(CLEAR_2);
		//モード設定(クリア画面に移行)
		SetFade(MODE_CLEAR);
	}
}

//==============================================================
//ゲーム画面の描画処理
//==============================================================
void DrawStage4(void)
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
	DrawSphere();
	DrawBillboard();
	DrawExplosion();
	DrawShadow();
}