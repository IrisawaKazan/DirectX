//==============================================================
//
//3D_GAME[shadow.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"shadow.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//���_�o�b�t�@�ւ̃|�C���^
Shadow g_aShadow[MAX_SHADOW];

//==============================================================
//�e�̏���������
//==============================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntShadow;

	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.png",
		&g_pTextureShadow);

	//�e�̏��̏�����
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].mtxWorld = {};
		g_aShadow[nCntShadow].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-15.0f, 0.1f, 15.0f);
		pVtx[1].pos = D3DXVECTOR3(15.0f, 0.1f, 15.0f);
		pVtx[2].pos = D3DXVECTOR3(-15.0f, 0.1f, -15.0f);
		pVtx[3].pos = D3DXVECTOR3(15.0f, 0.1f, -15.0f);

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

	g_pVtxBuffShadow->Unlock();
}

//==============================================================
//�e�̏I������
//==============================================================
void UninitShadow(void)
{
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//==============================================================
//�e�̍X�V����
//==============================================================
void UpdateShadow(void)
{

}

//==============================================================
//�e�̕`�揈��
//==============================================================
void DrawShadow(void)
{
	Player* pPlayer = GetPlayer();

	if (pPlayer->bDisp == true)
	{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		pDevice = GetDevice();

		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
		{
			if (g_aShadow[nCntShadow].bUse == true)
			{
				//�v�Z�p�̃}�g���b�N�X
				D3DXMATRIX mtxRot, mtxTrans;

				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
				D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
				D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

				//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

				//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureShadow);

				//�e�̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					4 * nCntShadow,
					2);
			}
		}

		//�ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//==============================================================
//�e�̐ݒ菈��
//==============================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;

			break;
		}
	}
	return nCntShadow;//�e�̔ԍ�(index)��Ԃ�
}

//==============================================================
//�e�̈ʒu�̍X�V����
//==============================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}

//==============================================================
//�e����������
//==============================================================
void ShadowEX(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}