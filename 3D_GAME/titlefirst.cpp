//==============================================================
//
//3D_GAME[titlefirst.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"titlefirst.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTitlefirst = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlefirst = NULL;//���_�o�b�t�@�̃|�C���^

//==============================================================
//�^�C�g���t�@�[�X�g��ʂ̏���������
//==============================================================
void InitTitlefirst(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title100.png",//�^�C�g���ƃT�u�^�C�g���� �ł��邾�����ƍ�������
		&g_pTextureTitlefirst);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlefirst,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitlefirst->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitlefirst->Unlock();
}

//==============================================================
//�^�C�g���t�@�[�X�g��ʂ̏I������
//==============================================================
void UninitTitlefirst(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTitlefirst != NULL)
	{
		g_pTextureTitlefirst->Release();
		g_pTextureTitlefirst = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitlefirst != NULL)
	{
		g_pVtxBuffTitlefirst->Release();
		g_pVtxBuffTitlefirst = NULL;
	}
}

//==============================================================
//�^�C�g���t�@�[�X�g��ʂ̍X�V����
//==============================================================
void UpdateTitlefirst(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{//����L�[(ENTER�L�[)�������ꂽ
		//���[�h�ݒ�(�`���[�g���A����ʂɈڍs)
		SetFade(MODE_TUTORIAL);
	}
}

//==============================================================
//�^�C�g���t�@�[�X�g��ʂ̕`�揈��
//==============================================================
void DrawTitlefirst(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitlefirst, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitlefirst);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}