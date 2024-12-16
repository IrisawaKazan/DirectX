//==============================================================
//
//[meshhole.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"meshhole.h"

//�O���[�o���ϐ�
Meshhole g_meshhole;

//==============================================================
//���b�V���z�[���̏���������
//==============================================================
void InitMeshhole(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_meshhole.pTexture = NULL;
	g_meshhole.pVtxBuff = NULL;
	g_meshhole.pIdxBuff = NULL;
	g_meshhole.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshhole.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshhole.mtxWorld = {};

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\",
		&g_meshhole.pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MHPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_meshhole.pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MHPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshhole.pIdxBuff,
		NULL);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_meshhole.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-MAX_MHPOS / 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[1].pos = D3DXVECTOR3(-MAX_MHPOS, MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[2].pos = D3DXVECTOR3(-MAX_MHPOS, -MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[3].pos = D3DXVECTOR3(-MAX_MHPOS / 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[4].pos = D3DXVECTOR3(MAX_MHPOS / 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[5].pos = D3DXVECTOR3(MAX_MHPOS, -MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[6].pos = D3DXVECTOR3(MAX_MHPOS, MAX_MHPOS / 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[7].pos = D3DXVECTOR3(MAX_MHPOS / 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[8].pos = D3DXVECTOR3(-MAX_MHPOS / 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[9].pos = D3DXVECTOR3(-MAX_MHPOS, MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[10].pos = D3DXVECTOR3(-MAX_MHPOS * 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[11].pos = D3DXVECTOR3(-MAX_MHPOS * 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[12].pos = D3DXVECTOR3(-MAX_MHPOS, -MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[13].pos = D3DXVECTOR3(MAX_MHPOS, -MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[14].pos = D3DXVECTOR3(MAX_MHPOS * 2.0f, -MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[15].pos = D3DXVECTOR3(MAX_MHPOS * 2.0f, MAX_MHPOS + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[16].pos = D3DXVECTOR3(MAX_MHPOS, MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);
	pVtx[17].pos = D3DXVECTOR3(-MAX_MHPOS, MAX_MHPOS * 2.0f + MAX_MHHEIGHT, MAX_MHZ);

	for (int nCntMeshwall = 0; nCntMeshwall < MAX_MHPVTX; nCntMeshwall++)
	{
		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[nCntMeshwall].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[nCntMeshwall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / 8.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f / 8.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(3.0f / 8.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(4.0f / 8.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(5.0f / 8.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(6.0f / 8.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(7.0f / 8.0f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(1.0f / 8.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(2.0f / 8.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(3.0f / 8.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(4.0f / 8.0f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(5.0f / 8.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(6.0f / 8.0f, 1.0f);
	pVtx[16].tex = D3DXVECTOR2(7.0f / 8.0f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_meshhole.pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐����E�C���f�b�N�X���̐ݒ�
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_meshhole.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	pIdx[0] = 9;
	pIdx[1] = 0;
	pIdx[2] = 10;
	pIdx[3] = 1;
	pIdx[4] = 11;
	pIdx[5] = 2;
	pIdx[6] = 12;
	pIdx[7] = 3;
	pIdx[8] = 13;
	pIdx[9] = 4;
	pIdx[10] = 14;
	pIdx[11] = 5;
	pIdx[12] = 15;
	pIdx[13] = 6;
	pIdx[14] = 16;
	pIdx[15] = 7;
	pIdx[16] = 17;
	pIdx[17] = 8;

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_meshhole.pIdxBuff->Unlock();
}

//==============================================================
//���b�V���E�H�[���̏I������
//==============================================================
void UninitMeshhole(void)
{
	if (g_meshhole.pTexture != NULL)
	{
		g_meshhole.pTexture->Release();
		g_meshhole.pTexture = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_meshhole.pVtxBuff != NULL)
	{
		g_meshhole.pVtxBuff->Release();
		g_meshhole.pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_meshhole.pIdxBuff != NULL)
	{
		g_meshhole.pIdxBuff->Release();
		g_meshhole.pIdxBuff = NULL;
	}
}

//==============================================================
//���b�V���E�H�[���̍X�V����
//==============================================================
void UpdateMeshhole(void)
{

}

//==============================================================
//���b�V���E�H�[���̕`�揈��
//==============================================================
void DrawMeshhole(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshhole.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshhole.rot.y, g_meshhole.rot.x, g_meshhole.rot.z);
	D3DXMatrixMultiply(&g_meshhole.mtxWorld, &g_meshhole.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_meshhole.pos.x, g_meshhole.pos.y, g_meshhole.pos.z);
	D3DXMatrixMultiply(&g_meshhole.mtxWorld, &g_meshhole.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_meshhole.mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_meshhole.pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_meshhole.pIdxBuff);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_meshhole.pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MHPVTX, 0, MAX_MHPOLYGON);
}