//==============================================================
//
//3D_GAME[pause.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"pause.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_aVtxBuffPause = NULL;//���_�o�b�t�@�ւ̃|�C���^
PAUSE_MENU g_pauseMenu;                        //�|�[�Y���j���[
int g_nPause;

//==============================================================
//�|�[�Y�̏���������
//==============================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause101.png",//1.���̃X�e�[�W�̍ŏ����� 2.�^�C�g���֖߂�
		&g_pTexturePause);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_aVtxBuffPause,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_aVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_aVtxBuffPause->Unlock();
}

//==============================================================
//�|�[�Y�̏I������
//==============================================================
void UninitPause(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_aVtxBuffPause != NULL)
	{
		g_aVtxBuffPause->Release();
		g_aVtxBuffPause = NULL;
	}
}

//==============================================================
//�|�[�Y�̍X�V����
//==============================================================
void UpdatePause(void)
{
	if (GetKeyboardTrigger(DIK_1) == true)
	{//���̃X�e�[�W�̍ŏ������蒼��
		SetFade(MODE_GAME);
	}
	else if (GetKeyboardTrigger(DIK_2) == true)
	{//�^�C�g���ɖ߂�
		SetStage(STAGE_1);
		SetFade(MODE_TITLE);
	}
	//���R�}���h
	else if (GetKeyboardTrigger(DIK_5) == true)
	{//�`���[�g���A����ʂɍs��
		SetFade(MODE_TUTORIAL);
	}
	else if (GetKeyboardTrigger(DIK_6) == true)
	{//�Q�[���I�[�o�[��ʂɍs��
		SetFade(MODE_GAMEOVER);
	}
	else if (GetKeyboardTrigger(DIK_7) == true)
	{//���U���g��ʂɍs��
		SetFade(MODE_RESULT);
	}
	else if (GetKeyboardTrigger(DIK_8) == true)
	{//�N���A��ʂɍs��
		SetFade(MODE_CLEAR);
	}
	else if (GetKeyboardTrigger(DIK_9) == true)
	{//�X�e�[�W1�ɍs��
		SetStage(STAGE_1);
		SetFade(MODE_GAME);
	}
	else if (GetKeyboardTrigger(DIK_0) == true)
	{//�X�e�[�W2�ɍs��
		SetStage(STAGE_2);
		SetFade(MODE_GAME);
	}
	else if (GetKeyboardTrigger(DIK_BACKSPACE) == true)
	{//�X�e�[�W3�ɍs��
		SetStage(STAGE_3);
		SetFade(MODE_GAME);
	}
	else if (GetKeyboardTrigger(DIK_DELETE) == true)
	{//�X�e�[�W4�ɍs��
		SetStage(STAGE_4);
		SetFade(MODE_GAME);
	}
}

//==============================================================
//�|�[�Y�̕`�揈��
//==============================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPause;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_aVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	for (nCntPause = 0; nCntPause < 8; nCntPause++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCntPause,
			2);
	}
}