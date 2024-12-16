//==============================================================
//
//ACTION_GAME[stage1.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"stage1.h"
#include"game.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"pause.h"
#include"fade.h"

//==============================================================
//�Q�[����ʂ̏���������
//==============================================================
void InitStage1(void)
{
	InitBackground();

	InitBlock();

	//SetBlock:37

	//���[�̕�
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

	//��
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

	//�i��1
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 450.0f - 50.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 450.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));

	//�����Ă���u���b�N1 - �^�C�v�ς���
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, SCREEN_HEIGHT - 240.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, SCREEN_HEIGHT - 240.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1125.0f, SCREEN_HEIGHT - 240.0f, 0.0f));

	//�� - �^�C�v�ς���
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 225.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 175.0f, 0.0f));

	////����m�F�p
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 150.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1100.0f, SCREEN_HEIGHT - 300.0f, 0.0f));

	// + 19
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
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 225.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 325.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 375.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 425.0f, 0.0f));
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 475.0f, 0.0f));

	InitPlayer();
}

//==============================================================
//�Q�[����ʂ̏I������
//==============================================================
void UninitStage1(void)
{
	UninitBackground();

	UninitBlock();

	UninitPlayer();
}

//==============================================================
//�Q�[����ʂ̍X�V����
//==============================================================
void UpdateStage1(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	UpdateBackground();

	UpdateBlock();

	UpdatePlayer();

	//if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	//{//����L�[(ENTER�L�[)�������ꂽ
	//	//���[�h�ݒ�(���U���g��ʂɈڍs)
	//	SetFade(MODE_RESULT);
	//}
	if (pPlayer->pos.y >= SCREEN_HEIGHT + 150.0f && GetFade() == FADE_NONE)
	{//���������ʂ�J�ڂ���
		pPlayer->bDisp = false;
		//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
		SetFade(MODE_GAMEOVER);
	}
	if (pPlayer->pos.x <= -25.0f && GetFade() == FADE_NONE)
	{//�ŏ��̉�ʂ̍��ɍs�������ʂ�J�ڂ���
		pPlayer->bDisp = false;
		//���[�h�ݒ�(�^�C�g����ʂɈڍs)
		SetFade(MODE_TITLE);
	}
	if (pPlayer->pos.x >= SCREEN_WIDTH + 25.0f && GetFade() == FADE_NONE)
	{//�ŏ��̉�ʂ̉E�ɍs�������ʂ�J�ڂ���
		pPlayer->bDisp = false;
		SetStage(STAGE_2);
		//���̃X�e�[�W�Ɉڍs
		SetFade(MODE_GAME);
	}
}

//==============================================================
//�Q�[����ʂ̕`�揈��
//==============================================================
void DrawStage1(void)
{
	DrawBackground();

	DrawBlock();

	DrawPlayer();
}