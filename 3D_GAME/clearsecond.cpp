//==============================================================
//
//3D_GAME[clearsecond.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"clearsecond.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureClearsecond = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClearsecond = NULL;//���_�o�b�t�@�̃|�C���^

//==============================================================
//�N���A��ʂ̏���������
//==============================================================
void InitClearsecond(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clearsecond100.png",
		&g_pTextureClearsecond);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClearsecond,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffClearsecond->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffClearsecond->Unlock();
}

//==============================================================
//�N���A��ʂ̏I������
//==============================================================
void UninitClearsecond(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureClearsecond != NULL)
	{
		g_pTextureClearsecond->Release();
		g_pTextureClearsecond = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffClearsecond != NULL)
	{
		g_pVtxBuffClearsecond->Release();
		g_pVtxBuffClearsecond = NULL;
	}
}

//==============================================================
//�N���A��ʂ̍X�V����
//==============================================================
void UpdateClearsecond(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{//����L�[(ENTER�L�[)�������ꂽ
		SetStage(STAGE_1);
		SetTitle(TITLE_3);
		SetResult(RESULT_2);
		//���[�h�ݒ�(�^�C�g����ʂɈڍs)
		SetFade(MODE_TITLE);
	}
}

//==============================================================
//�N���A��ʂ̕`�揈��
//==============================================================
void DrawClearsecond(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffClearsecond, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureClearsecond);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}