//==============================================================
//
//[stage2.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"stage2.h"

//==============================================================
//�Q�[����ʂ̏���������
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

	//�S�[��
	SetGoal(D3DXVECTOR3(0.0f, GOAL_HEIGHT, 150.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�f�b�h�u���b�N
	{
		//�����Ȃ�
		SetDeadBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		//��
		SetDeadBlock(D3DXVECTOR3(-120.0f, 0.0f, -120.0f), 1);
		SetDeadBlock(D3DXVECTOR3(-80.0f, 0.0f, -80.0f), 1);
		//��
		SetDeadBlock(D3DXVECTOR3(200.0f, 0.0f, -120.0f), 2);
		//��
		SetDeadBlock(D3DXVECTOR3(20.0f, 0.0f, -400.0f), 3);
		//��

	}

	//�n�C�X�s�[�h�f�b�h�u���b�N
	{
		//��
		SetDeadBlockHS(D3DXVECTOR3(-400.0f, 0.0f, -40.0f), 1);
		//��
		
		//��

		//��

		//����

		//����

		//����
		SetDeadBlockHS(D3DXVECTOR3(-40.0f, 0.0f, -800.0f), 7);
		SetDeadBlockHS(D3DXVECTOR3(40.0f, 0.0f, -800.0f), 7);
		//����

	}

	//�S�[���u���b�N��
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

	//���X�g�u���b�N
	{
		//��
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, -120.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, -80.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, -40.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 0.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 40.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 80.0f), 1);
		SetLastBlock(D3DXVECTOR3(-MAX_LBLOCKPOSS2, 0.0f, 120.0f), 1);
		//��
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 120.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 80.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 40.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, 0.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, -40.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, -80.0f), 2);
		SetLastBlock(D3DXVECTOR3(MAX_LBLOCKPOSS2, 0.0f, -120.0f), 2);
		//��
		SetLastBlock(D3DXVECTOR3(120.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(80.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(40.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(0.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(-40.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(-80.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		SetLastBlock(D3DXVECTOR3(-120.0f, 0.0f, -MAX_LBLOCKPOSS2), 3);
		//��
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
//�Q�[����ʂ̏I������
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
//�Q�[����ʂ̍X�V����
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
	if (pPlayer->pos.z >= 140.0f && GetFade() == FADE_NONE)
	{//�N���A
		//���[�h�ݒ�(  ��ʂɈڍs)
		SetFade(MODE_CLEAR);
	}
}

//==============================================================
//�Q�[����ʂ̕`�揈��
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