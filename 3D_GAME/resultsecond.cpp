//==============================================================
//
//3D_GAME[resultsecond.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"resultsecond.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResultSecond = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultSecond = NULL;//���_�o�b�t�@�̃|�C���^

//==============================================================
//���U���g��ʂ̏���������
//==============================================================
void InitResultSecond(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\result101.png",
		&g_pTextureResultSecond);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultSecond,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffResultSecond->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultSecond->Unlock();
}

//==============================================================
//���U���g��ʂ̏I������
//==============================================================
void UninitResultSecond(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureResultSecond != NULL)
	{
		g_pTextureResultSecond->Release();
		g_pTextureResultSecond = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResultSecond != NULL)
	{
		g_pVtxBuffResultSecond->Release();
		g_pVtxBuffResultSecond = NULL;
	}
}

//==============================================================
//���U���g��ʂ̍X�V����
//==============================================================
void UpdateResultSecond(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) == true && GetFade() == FADE_NONE)
	{
		//���[�h�ݒ�(�^�C�g����ʂɈڍs)
		SetFade(MODE_TITLE);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetStage(STAGE_2);
		//���̃X�e�[�W�Ɉڍs
		SetFade(MODE_GAME);
	}
}

//==============================================================
//���U���g��ʂ̕`�揈��
//==============================================================
void DrawResultSecond(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultSecond, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultSecond);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}