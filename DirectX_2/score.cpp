//==============================================================
//
//SHOOTING GAME[score.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"score.h"
#include"main.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posScore;                        //�X�R�A�̈ʒu
int g_nScore;                                  //�X�R�A�̒l

//==============================================================
//�X�R�A�̏���������
//==============================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, 
		"data\\TEXTURE\\number100.png", 
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������
	g_nScore = 0;                              //�l������������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, 
		&g_pVtxBuffScore, 
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//�X�R�A�̏I������
//==============================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//==============================================================
//�X�R�A�̍X�V����
//==============================================================
void UpdateScore(void)
{
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//�X�R�A�̕`�揈��
//==============================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		if (g_nScore == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				4 * 8, 
				2);
		}
	}
}

//==============================================================
//�X�R�A�̐ݒ菈��
//==============================================================
void SetScore(int nScore)
{
	int aPosTexU[8];//�e���̐������i�[
	g_nScore = nScore;

	int nCntScore;

	aPosTexU[0] = g_nScore;
	aPosTexU[1] = g_nScore;
	aPosTexU[2] = g_nScore;
	aPosTexU[3] = g_nScore;
	aPosTexU[4] = g_nScore;
	aPosTexU[5] = g_nScore;
	aPosTexU[6] = g_nScore;
	aPosTexU[7] = g_nScore;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//�X�R�A�̉��Z����
//==============================================================
void AddScore(int nValue)
{
	int aPosTexU[8];//�e���̐������i�[
	g_nScore += nValue;

	int nCntScore;

	aPosTexU[0] = g_nScore;
	aPosTexU[1] = g_nScore;
	aPosTexU[2] = g_nScore;
	aPosTexU[3] = g_nScore;
	aPosTexU[4] = g_nScore;
	aPosTexU[5] = g_nScore;
	aPosTexU[6] = g_nScore;
	aPosTexU[7] = g_nScore;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//==============================================================
//�X�R�A�̎擾����
//==============================================================
int GetScore(void)
{
	return g_nScore;
}