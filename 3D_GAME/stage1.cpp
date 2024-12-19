//==============================================================
//
//3D_GAME[stage1.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"stage1.h"

//==============================================================
//�Q�[����ʂ̏���������
//==============================================================
void InitStage1(void)
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
	//InitSound(HWND(-1));

	//�r���{�[�h(�_)
	SetBillboard(D3DXVECTOR3(-200.0f, 80.0f, 200.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 80.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(-40.0f, -100.0f, -200.0f));

	//�S�[��
	SetGoal(D3DXVECTOR3(0.0f, GOAL_HEIGHT, 150.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�f�b�h�u���b�N
	{
		//��
		SetDeadBlock(D3DXVECTOR3(-400.0f, 0.0f, -40.0f), 1);
		SetDeadBlock(D3DXVECTOR3(-400.0f, 0.0f, 0.0f), 1);
		SetDeadBlock(D3DXVECTOR3(-600.0f, 0.0f, -80.0f), 1);
		SetDeadBlock(D3DXVECTOR3(-600.0f, 0.0f, -40.0f), 1);
		SetDeadBlock(D3DXVECTOR3(-600.0f, 0.0f, 0.0f), 1);
		//��
		SetDeadBlock(D3DXVECTOR3(400.0f, 0.0f, 0.0f), 2);
		SetDeadBlock(D3DXVECTOR3(400.0f, 0.0f, 40.0f), 2);
		SetDeadBlock(D3DXVECTOR3(600.0f, 0.0f, 0.0f), 2);
		SetDeadBlock(D3DXVECTOR3(600.0f, 0.0f, 40.0f), 2);
		SetDeadBlock(D3DXVECTOR3(600.0f, 0.0f, 80.0f), 2);
		//��
		SetDeadBlock(D3DXVECTOR3(-120.0f, 0.0f, -400.0f), 3);
		SetDeadBlock(D3DXVECTOR3(0.0f, 0.0f, -400.0f), 3);
		SetDeadBlock(D3DXVECTOR3(120.0f, 0.0f, -400.0f), 3);
		//��
		SetDeadBlock(D3DXVECTOR3(-50.0f, 0.0f, 50.0f), 4);
		SetDeadBlock(D3DXVECTOR3(0.0f, 0.0f, 150.0f), 4);
		SetDeadBlock(D3DXVECTOR3(50.0f, 0.0f, 100.0f), 4);
		SetDeadBlock(D3DXVECTOR3(100.0f, 0.0f, 0.0f), 4);
	}

	//�n�C�X�s�[�h�f�b�h�u���b�N
	{
		//��
		SetDeadBlockHS(D3DXVECTOR3(-700.0f, 0.0f, 120.0f), 1);
		SetDeadBlockHS(D3DXVECTOR3(-500.0f, 0.0f, -120.0f), 1);
		//��
		SetDeadBlockHS(D3DXVECTOR3(600.0f, 0.0f, -60.0f), 2);
		SetDeadBlockHS(D3DXVECTOR3(650.0f, 0.0f, 60.0f), 2);
		//��

		//��

		//����
		SetDeadBlockHS(D3DXVECTOR3(-1750.0f, 0.0f, 0.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2000.0f, 0.0f, -120.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2200.0f, 0.0f, -40.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-2400.0f, 0.0f, -120.0f), 5);
		SetDeadBlockHS(D3DXVECTOR3(-3000.0f, 0.0f, 120.0f), 5);
		//����
		SetDeadBlockHS(D3DXVECTOR3(2200.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(2300.0f, 0.0f, 80.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(2600.0f, 0.0f, 120.0f), 6);
		SetDeadBlockHS(D3DXVECTOR3(3200.0f, 0.0f, 120.0f), 6);
		//����
		SetDeadBlockHS(D3DXVECTOR3(-100.0f, 0.0f, -700.0f), 7);
		//����

	}

	//�S�[���u���b�N��
	{
		SetGoalBlock(D3DXVECTOR3(-160.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(-120.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(-80.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(-40.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(0.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(40.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(80.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(120.0f, 0.0f, MAX_GBLOCKPOS), 1);
		SetGoalBlock(D3DXVECTOR3(160.0f, 0.0f, MAX_GBLOCKPOS), 1);
	}

	//���X�g�u���b�N
	{
		//��
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS1, 0.0f, -120.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS1, 0.0f, -80.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS1, 0.0f, -40.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS1, 0.0f, 0.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS1, 0.0f, 40.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS1, 0.0f, 80.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS1, 0.0f, 120.0f), 1);
		//��
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS1, 0.0f, 120.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS1, 0.0f, 80.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS1, 0.0f, 40.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS1, 0.0f, 0.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS1, 0.0f, -40.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS1, 0.0f, -80.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS1, 0.0f, -120.0f), 2);
		//��
		SetLastBlock(D3DXVECTOR3(120.0f, 0.0f, -MAX_LBLOCKPOSS1), 3);
		SetLastBlock(D3DXVECTOR3(80.0f, 0.0f, -MAX_LBLOCKPOSS1), 3);
		SetLastBlock(D3DXVECTOR3(40.0f, 0.0f, -MAX_LBLOCKPOSS1), 3);
		SetLastBlock(D3DXVECTOR3(0.0f, 0.0f, -MAX_LBLOCKPOSS1), 3);
		SetLastBlock(D3DXVECTOR3(-40.0f, 0.0f, -MAX_LBLOCKPOSS1), 3);
		SetLastBlock(D3DXVECTOR3(-80.0f, 0.0f, -MAX_LBLOCKPOSS1), 3);
		SetLastBlock(D3DXVECTOR3(-120.0f, 0.0f, -MAX_LBLOCKPOSS1), 3);
		//��
		SetLastBlock(D3DXVECTOR3(-120.0f, 0.0f, MAX_LBLOCKPOSS1), 4);
		SetLastBlock(D3DXVECTOR3(-80.0f, 0.0f, MAX_LBLOCKPOSS1), 4);
		SetLastBlock(D3DXVECTOR3(-40.0f, 0.0f, MAX_LBLOCKPOSS1), 4);
		SetLastBlock(D3DXVECTOR3(0.0f, 0.0f, MAX_LBLOCKPOSS1), 4);
		SetLastBlock(D3DXVECTOR3(40.0f, 0.0f, MAX_LBLOCKPOSS1), 4);
		SetLastBlock(D3DXVECTOR3(80.0f, 0.0f, MAX_LBLOCKPOSS1), 4);
		SetLastBlock(D3DXVECTOR3(120.0f, 0.0f, MAX_LBLOCKPOSS1), 4);
	}
}

//==============================================================
//�Q�[����ʂ̏I������
//==============================================================
void UninitStage1(void)
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
	//UninitSound();
}

//==============================================================
//�Q�[����ʂ̍X�V����
//==============================================================
void UpdateStage1(void)
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

	if (pPlayer->pos.z <= -150.0f && GetFade() == FADE_NONE)
	{//�Q�[���I�[�o�[
		pPlayer->bDisp = false;
		//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x <= -150.0f && GetFade() == FADE_NONE)
	{//�Q�[���I�[�o�[
		pPlayer->bDisp = false;
		//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x >= 150.0f && GetFade() == FADE_NONE)
	{//�Q�[���I�[�o�[
		pPlayer->bDisp = false;
		//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.z >= 142.0f && GetFade() == FADE_NONE)
	{//�N���A
		//���[�h�ݒ�(���U���g��ʂɈڍs)
		SetFade(MODE_RESULT);
	}
}

//==============================================================
//�Q�[����ʂ̕`�揈��
//==============================================================
void DrawStage1(void)
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
	DrawShadow();
}