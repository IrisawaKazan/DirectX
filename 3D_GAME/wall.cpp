//==============================================================
//
//[wall.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"wall.h"

//�O���[�o���ϐ�
Wall g_aWall[MAX_WALL];
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//���_�o�b�t�@�ւ̃|�C���^

//==============================================================
//�ǂ̏���������
//==============================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntWall;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTextureWall);

	//�ǂ̏��̏�����
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].mtxWorld = {};
		g_aWall[nCntWall].nType = {};
		g_aWall[nCntWall].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH, 0.0f, WALL_HEIGHT);
		pVtx[1].pos = D3DXVECTOR3(WALL_WIDTH, 0.0f, WALL_HEIGHT);
		pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH, 0.0f, -WALL_HEIGHT);
		pVtx[3].pos = D3DXVECTOR3(WALL_WIDTH, 0.0f, -WALL_HEIGHT);

		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//==============================================================
//�ǂ̏I������
//==============================================================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//==============================================================
//�ǂ̍X�V����
//==============================================================
void UpdateWall(void)
{

}

//==============================================================
//�ǂ̕`�揈��
//==============================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//�v�Z�p�̃}�g���b�N�X
			D3DXMATRIX mtxRot, mtxTrans;

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntWall,
				2);
		}
	}
}

//==============================================================
//�ǂ̐ݒ菈��
//==============================================================
int SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	int nCntWall;
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].col = col;

			g_aWall[nCntWall].bUse = true;

			//���_�J���[ RGBA
			pVtx[0].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);
			pVtx[1].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);
			pVtx[2].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);
			pVtx[3].col = D3DXCOLOR(g_aWall[nCntWall].col.r, g_aWall[nCntWall].col.g, g_aWall[nCntWall].col.b, g_aWall[nCntWall].col.a);

			break;
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	return nCntWall;//�ǂ̔ԍ�(index)��Ԃ�
}

//==============================================================
//�ǂ̓����蔻�菈��
//==============================================================
void CollisionWall(void)
{
	Player* pPlayer = GetPlayer();


}