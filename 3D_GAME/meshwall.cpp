//==============================================================
//
//[meshwall.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"meshwall.h"

//�O���[�o���ϐ�
Meshwall g_meshwall;

//==============================================================
//���b�V���E�H�[���̏���������
//==============================================================
void InitMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_meshwall.pTexture = NULL;
	g_meshwall.pVtxBuff = NULL;
	g_meshwall.pIdxBuff = NULL;
	g_meshwall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshwall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshwall.mtxWorld = {};

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_meshwall.pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MWPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_meshwall.pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MWPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshwall.pIdxBuff,
		NULL);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_meshwall.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = -D3DXVECTOR3(-MAX_MWPOSX, MAX_MWHEIGHT, MAX_MWPOSZ);
	pVtx[1].pos = -D3DXVECTOR3(0.0f, MAX_MWHEIGHT, MAX_MWPOSZ);
	pVtx[2].pos = -D3DXVECTOR3(MAX_MWPOSX, MAX_MWHEIGHT, MAX_MWPOSZ);
	pVtx[3].pos = -D3DXVECTOR3(-MAX_MWPOSX, MAX_MWHEIGHT / 2.0f, MAX_MWPOSZ);
	pVtx[4].pos = -D3DXVECTOR3(0.0f, MAX_MWHEIGHT / 2.0f, MAX_MWPOSZ);
	pVtx[5].pos = -D3DXVECTOR3(MAX_MWPOSX, MAX_MWHEIGHT / 2.0f, MAX_MWPOSZ);
	pVtx[6].pos = -D3DXVECTOR3(-MAX_MWPOSX, 0.0f, MAX_MWPOSZ);
	pVtx[7].pos = -D3DXVECTOR3(0.0f, 0.0f, MAX_MWPOSZ);
	pVtx[8].pos = -D3DXVECTOR3(MAX_MWPOSX, 0.0f, MAX_MWPOSZ);

	for (int nCntMeshwall = 0; nCntMeshwall < MAX_MWPVTX; nCntMeshwall++)
	{
		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[nCntMeshwall].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[nCntMeshwall].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
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
	g_meshwall.pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐����E�C���f�b�N�X���̐ݒ�
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_meshwall.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

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
	g_meshwall.pIdxBuff->Unlock();
}

//==============================================================
//���b�V���E�H�[���̏I������
//==============================================================
void UninitMeshwall(void)
{
	if (g_meshwall.pTexture != NULL)
	{
		g_meshwall.pTexture->Release();
		g_meshwall.pTexture = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_meshwall.pVtxBuff != NULL)
	{
		g_meshwall.pVtxBuff->Release();
		g_meshwall.pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_meshwall.pIdxBuff != NULL)
	{
		g_meshwall.pIdxBuff->Release();
		g_meshwall.pIdxBuff = NULL;
	}
}

//==============================================================
//���b�V���E�H�[���̍X�V����
//==============================================================
void UpdateMeshwall(void)
{

}

//==============================================================
//���b�V���E�H�[���̕`�揈��
//==============================================================
void DrawMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshwall.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshwall.rot.y, g_meshwall.rot.x, g_meshwall.rot.z);
	D3DXMatrixMultiply(&g_meshwall.mtxWorld, &g_meshwall.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_meshwall.pos.x, g_meshwall.pos.y, g_meshwall.pos.z);
	D3DXMatrixMultiply(&g_meshwall.mtxWorld, &g_meshwall.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_meshwall.mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_meshwall.pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_meshwall.pIdxBuff);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_meshwall.pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MWPVTX, 0, MAX_MWPOLYGON);
}