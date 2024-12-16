//==============================================================
//
//3D_GAME[meshfield.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"meshfield.h"

//�O���[�o���ϐ�
Meshfield g_meshfield;

//==============================================================
//���b�V���t�B�[���h�̏���������
//==============================================================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_meshfield.pTexture = NULL;
	g_meshfield.pVtxBuff = NULL;
	g_meshfield.pIdxBuff = NULL;
	g_meshfield.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshfield.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshfield.mtxWorld = {};

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field100.png",
		&g_meshfield.pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MFPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_meshfield.pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MFPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshfield.pIdxBuff,
		NULL);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_meshfield.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-MAX_MFPOS, 0.0f, MAX_MFPOS);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, MAX_MFPOS);
	pVtx[2].pos = D3DXVECTOR3(MAX_MFPOS, 0.0f, MAX_MFPOS);
	pVtx[3].pos = D3DXVECTOR3(-MAX_MFPOS, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(MAX_MFPOS, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-MAX_MFPOS, 0.0f, -MAX_MFPOS);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -MAX_MFPOS);
	pVtx[8].pos = D3DXVECTOR3(MAX_MFPOS, 0.0f, -MAX_MFPOS);

	for (int nCntMeshfield = 0; nCntMeshfield < MAX_MFPVTX; nCntMeshfield++)
	{
		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[nCntMeshfield].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[nCntMeshfield].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_meshfield.pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐����E�C���f�b�N�X���̐ݒ�
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_meshfield.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	//�C���f�b�N�X�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_meshfield.pIdxBuff->Unlock();
}

//==============================================================
//���b�V���t�B�[���h�̏I������
//==============================================================
void UninitMeshfield(void)
{
	if (g_meshfield.pTexture != NULL)
	{
		g_meshfield.pTexture->Release();
		g_meshfield.pTexture = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_meshfield.pVtxBuff != NULL)
	{
		g_meshfield.pVtxBuff->Release();
		g_meshfield.pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_meshfield.pIdxBuff != NULL)
	{
		g_meshfield.pIdxBuff->Release();
		g_meshfield.pIdxBuff = NULL;
	}
}

//==============================================================
//���b�V���t�B�[���h�̍X�V����
//==============================================================
void UpdateMeshfield(void)
{

}

//==============================================================
//���b�V���t�B�[���h�̕`�揈��
//==============================================================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshfield.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshfield.rot.y, g_meshfield.rot.x, g_meshfield.rot.z);
	D3DXMatrixMultiply(&g_meshfield.mtxWorld, &g_meshfield.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_meshfield.pos.x, g_meshfield.pos.y, g_meshfield.pos.z);
	D3DXMatrixMultiply(&g_meshfield.mtxWorld, &g_meshfield.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_meshfield.mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_meshfield.pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_meshfield.pIdxBuff);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_meshfield.pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MFPVTX, 0, MAX_MFPOLYGON);
}