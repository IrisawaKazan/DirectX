//�R�s�[�p
//==============================================================
//
//[billboard.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"billboard.h"
#include"player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;//���_�o�b�t�@�ւ̃|�C���^
Billboard g_aBillboard[MAX_BILLBOARD];             //�r���{�[�h���

//==============================================================
//�r���{�[�h�̏���������
//==============================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBillboard;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wood.png",
		&g_pTextureBillboard);

	//�r���{�[�h�̏��̏�����
	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aBillboard[nCntBillboard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aBillboard[nCntBillboard].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aBillboard[nCntBillboard].nLife = 100;
		//g_aBillboard[nCntBillboard].nType = {};
		g_aBillboard[nCntBillboard].mtxWorld = {};
		g_aBillboard[nCntBillboard].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-75.0f, 75.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(75.0f, 75.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-75.0f, -75.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(75.0f, -75.0f, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

	g_pVtxBuffBillboard->Unlock();
}

//==============================================================
//�r���{�[�h�̏I������
//==============================================================
void UninitBillboard(void)
{
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//==============================================================
//�r���{�[�h�̍X�V����
//==============================================================
void UpdateBillboard(void)
{
	//int nCntBillboard;
	//VERTEX_3D* pVtx;

	////���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	//g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	//{
	//	//�e�̈ʒu�̍X�V
	//	g_aBillboard[nCntBillboard].pos += g_aBillboard[nCntBillboard].move;

	//	//���_���W�̍X�V
	//	pVtx[0].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);

	//	if (g_aBillboard[nCntBillboard].pos.x > SCREEN_WIDTH + 25)
	//	{
	//		g_aBillboard[nCntBillboard].bUse = false;//�g�p���ĂȂ���Ԃɂ���
	//	}

	//	//�����̃J�E���g�_�E��
	//	g_aBillboard[nCntBillboard].nLife--;

	//	pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	//}

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffBillboard->Unlock();
}

//==============================================================
//�r���{�[�h�̕`�揈��
//==============================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			//�v�Z�p�̃}�g���b�N�X
			D3DXMATRIX mtxTrans, mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

			//�J�����̋t�s���ݒ�
			g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillboard);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBillboard,
				2);
		}
	}

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==============================================================
//�r���{�[�h�̐ݒ菈��
//==============================================================
void SetBillboard(D3DXVECTOR3 pos/*, D3DXVECTOR3 move, D3DXVECTOR3 dir, int nLife*/)
{
	int nCntBillboard;
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBillboard[nCntBillboard].pos = pos;
			//g_aBillboard[nCntBillboard].move = move;
			//g_aBillboard[nCntBillboard].dir = dir;
			//g_aBillboard[nCntBillboard].nLife = 300;

			g_aBillboard[nCntBillboard].bUse = true;//�g�p���Ă����Ԃɂ���

			//���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y - 25.0f, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x - 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x + 25.0f, g_aBillboard[nCntBillboard].pos.y + 25.0f, 0.0f);

			break;
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
}