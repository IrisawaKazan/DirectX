//==============================================================
//
//[column.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"column.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureColumn = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffColumn = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffColumn = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posColumn;                        //�ʒu
D3DXVECTOR3 g_rotColumn;                        //����
D3DXMATRIX g_mtxWorldColumn;                    //���[���h�}�g���b�N�X

//==============================================================
//�~���̏���������
//==============================================================
void InitColumn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.png",
		&g_pTextureColumn);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_CPVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffColumn,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_CPIDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffColumn,
		NULL);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffColumn->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, MAX_CPOS, -MAX_CPOS);
	pVtx[1].pos = D3DXVECTOR3(MAX_CPOS / 2.0f, MAX_CPOS, -MAX_CPOS /2.0f);
	pVtx[2].pos = D3DXVECTOR3(MAX_CPOS, MAX_CPOS, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MAX_CPOS / 2.0f, MAX_CPOS, MAX_CPOS / 2.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, MAX_CPOS, MAX_CPOS);
	pVtx[5].pos = D3DXVECTOR3(-MAX_CPOS / 2.0f, MAX_CPOS, MAX_CPOS / 2.0f);
	pVtx[6].pos = D3DXVECTOR3(-MAX_CPOS, MAX_CPOS, 0.0f);

	for (int nCntColumn = 0; nCntColumn < MAX_CPVTX; nCntColumn++)
	{
		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[nCntColumn].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[nCntColumn].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffColumn->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐����E�C���f�b�N�X���̐ݒ�
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffColumn->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffColumn->Unlock();
}

//==============================================================
//�~���̏I������
//==============================================================
void UninitColumn(void)
{
	if (g_pTextureColumn != NULL)
	{
		g_pTextureColumn->Release();
		g_pTextureColumn = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffColumn != NULL)
	{
		g_pVtxBuffColumn->Release();
		g_pVtxBuffColumn = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffColumn != NULL)
	{
		g_pIdxBuffColumn->Release();
		g_pIdxBuffColumn = NULL;
	}
}

//==============================================================
//�~���̍X�V����
//==============================================================
void UpdateColumn(void)
{

}

//==============================================================
//�~���̕`�揈��
//==============================================================
void DrawColumn(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldColumn);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotColumn.y, g_rotColumn.x, g_rotColumn.z);
	D3DXMatrixMultiply(&g_mtxWorldColumn, &g_mtxWorldColumn, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posColumn.x, g_posColumn.y, g_posColumn.z);
	D3DXMatrixMultiply(&g_mtxWorldColumn, &g_mtxWorldColumn, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldColumn);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffColumn, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffColumn);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureColumn);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_CPVTX, 0, MAX_CPOLYGON);
}