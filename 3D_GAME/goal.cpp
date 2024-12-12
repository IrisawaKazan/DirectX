//==============================================================
//
//[goal.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"goal.h"

//�O���[�o���ϐ�
Goal g_aGoal[MAX_GOAL];
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;//���_�o�b�t�@�ւ̃|�C���^

//==============================================================
//�S�[���̏���������
//==============================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntGoal;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\goal000.png",
		&g_pTextureGoal);

	//�ǂ̏��̏�����
	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		g_aGoal[nCntGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGoal[nCntGoal].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGoal[nCntGoal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGoal[nCntGoal].mtxWorld = {};
		g_aGoal[nCntGoal].nType = {};
		g_aGoal[nCntGoal].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-GOAL_WIDTH, 0.0f, GOAL_HEIGHT);
		pVtx[1].pos = D3DXVECTOR3(GOAL_WIDTH, 0.0f, GOAL_HEIGHT);
		pVtx[2].pos = D3DXVECTOR3(-GOAL_WIDTH, 0.0f, -GOAL_HEIGHT);
		pVtx[3].pos = D3DXVECTOR3(GOAL_WIDTH, 0.0f, -GOAL_HEIGHT);

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
	g_pVtxBuffGoal->Unlock();
}

//==============================================================
//�S�[���̏I������
//==============================================================
void UninitGoal(void)
{
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//==============================================================
//�S�[���̍X�V����
//==============================================================
void UpdateGoal(void)
{

}

//==============================================================
//�S�[���̕`�揈��
//==============================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_aGoal[nCntGoal].bUse == true)
		{
			//�v�Z�p�̃}�g���b�N�X
			D3DXMATRIX mtxRot, mtxTrans;

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aGoal[nCntGoal].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGoal[nCntGoal].rot.y, g_aGoal[nCntGoal].rot.x, g_aGoal[nCntGoal].rot.z);
			D3DXMatrixMultiply(&g_aGoal[nCntGoal].mtxWorld, &g_aGoal[nCntGoal].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aGoal[nCntGoal].pos.x, g_aGoal[nCntGoal].pos.y, g_aGoal[nCntGoal].pos.z);
			D3DXMatrixMultiply(&g_aGoal[nCntGoal].mtxWorld, &g_aGoal[nCntGoal].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aGoal[nCntGoal].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_3D));

			//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureGoal);

			//�ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntGoal,
				2);
		}
	}
}

//==============================================================
//�S�[���̐ݒ菈��
//==============================================================
int SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	int nCntGoal;
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_aGoal[nCntGoal].bUse == false)
		{
			g_aGoal[nCntGoal].pos = pos;
			g_aGoal[nCntGoal].rot = rot;
			g_aGoal[nCntGoal].col = col;

			g_aGoal[nCntGoal].bUse = true;

			//���_�J���[ RGBA
			pVtx[0].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);
			pVtx[1].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);
			pVtx[2].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);
			pVtx[3].col = D3DXCOLOR(g_aGoal[nCntGoal].col.r, g_aGoal[nCntGoal].col.g, g_aGoal[nCntGoal].col.b, g_aGoal[nCntGoal].col.a);

			break;
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();

	return nCntGoal;//�ǂ̔ԍ�(index)��Ԃ�
}