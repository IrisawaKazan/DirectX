//==============================================================
//
//[lastblock.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"lastblock.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureLastBlock[MAX_LBLOCK] = {};
LastBlock g_lastblock[MAX_LBLOCK];

//==============================================================
//���X�g�u���b�N�̏���������
//==============================================================
void InitLastBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		g_lastblock[nCntLastBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_lastblock[nCntLastBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].pMesh = NULL;
		g_lastblock[nCntLastBlock].pBuffMat = NULL;
		g_lastblock[nCntLastBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].dwNumMat = 0;
		g_lastblock[nCntLastBlock].mtxWorld = {};
		g_lastblock[nCntLastBlock].bUse = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\boxlast100.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_lastblock[nCntLastBlock].pBuffMat,
			NULL,
			&g_lastblock[nCntLastBlock].dwNumMat,
			&g_lastblock[nCntLastBlock].pMesh);

		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�̃|�C���^

		//���_���̎擾
		nNumVtx = g_lastblock[nCntLastBlock].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_lastblock[nCntLastBlock].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_lastblock[nCntLastBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l,�ő�l���擾
			if (vtx.x <= g_lastblock[nCntLastBlock].vtxMin.x)
			{
				g_lastblock[nCntLastBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_lastblock[nCntLastBlock].vtxMin.y)
			{
				g_lastblock[nCntLastBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_lastblock[nCntLastBlock].vtxMin.z)
			{
				g_lastblock[nCntLastBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_lastblock[nCntLastBlock].vtxMax.x)
			{
				g_lastblock[nCntLastBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_lastblock[nCntLastBlock].vtxMax.y)
			{
				g_lastblock[nCntLastBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_lastblock[nCntLastBlock].vtxMax.z)
			{
				g_lastblock[nCntLastBlock].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_lastblock[nCntLastBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_lastblock[nCntLastBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_lastblock[nCntLastBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���


				//�e�N�X�`���̓ǂݍ���


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureLastBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//���X�g�u���b�N�̏I������
//==============================================================
void UninitLastBlock(void)
{
	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		//���b�V���̔j��
		if (g_lastblock[nCntLastBlock].pMesh != NULL)
		{
			g_lastblock[nCntLastBlock].pMesh->Release();
			g_lastblock[nCntLastBlock].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_lastblock[nCntLastBlock].pBuffMat != NULL)
		{
			g_lastblock[nCntLastBlock].pBuffMat->Release();
			g_lastblock[nCntLastBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//���X�g�u���b�N�̍X�V����
//==============================================================
void UpdateLastBlock(void)
{
	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == true)
		{
			if (g_lastblock[nCntLastBlock].nType == 1)
			{
				//�E�ɓ���
				g_lastblock[nCntLastBlock].pos.x += sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.x += cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
			if (g_lastblock[nCntLastBlock].nType == 2)
			{
				//���ɓ���
				g_lastblock[nCntLastBlock].pos.x -= sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.x -= cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
			if (g_lastblock[nCntLastBlock].nType == 3)
			{
				//���ɓ���
				g_lastblock[nCntLastBlock].pos.x += sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.z += cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
			if (g_lastblock[nCntLastBlock].nType == 4)
			{
				//��O�ɓ���
				g_lastblock[nCntLastBlock].pos.x -= sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.z -= cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//���X�g�u���b�N�̕`�揈��
//==============================================================
void DrawLastBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_lastblock[nCntLastBlock].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_lastblock[nCntLastBlock].rot.y, g_lastblock[nCntLastBlock].rot.x, g_lastblock[nCntLastBlock].rot.z);
			D3DXMatrixMultiply(&g_lastblock[nCntLastBlock].mtxWorld, &g_lastblock[nCntLastBlock].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_lastblock[nCntLastBlock].pos.x, g_lastblock[nCntLastBlock].pos.y, g_lastblock[nCntLastBlock].pos.z);
			D3DXMatrixMultiply(&g_lastblock[nCntLastBlock].mtxWorld, &g_lastblock[nCntLastBlock].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_lastblock[nCntLastBlock].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_lastblock[nCntLastBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_lastblock[nCntLastBlock].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureLastBlock[nCntMat]);//����NULL

				//���f��(�p�[�c)�̕`��
				g_lastblock[nCntLastBlock].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A�������ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//���X�g�u���b�N�̐ݒ菈��
//==============================================================
void SetLastBlock(D3DXVECTOR3 pos, int type)
{
	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == false)
		{//�u���b�N�̎g�p����Ă��Ȃ�
			g_lastblock[nCntLastBlock].pos = pos;
			g_lastblock[nCntLastBlock].nType = type;

			g_lastblock[nCntLastBlock].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}

//==============================================================
//���X�g�u���b�N��X���̓����蔻�菈��
//==============================================================
void CollisionLastBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == true)
		{
			//���E�̂߂荞�ݔ���
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_lastblock[nCntLastBlock].pos.z + g_lastblock[nCntLastBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_lastblock[nCntLastBlock].pos.z - g_lastblock[nCntLastBlock].vtxMin.z * 2.0f)
			{
				//������E��
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_lastblock[nCntLastBlock].pos.x + g_lastblock[nCntLastBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_lastblock[nCntLastBlock].pos.x - g_lastblock[nCntLastBlock].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//���Q�[���I�[�o�[
						pPlayer->bDisp = false;
						//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
						SetFade(MODE_GAMEOVER);
					}
				}
				//�E���獶��
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_lastblock[nCntLastBlock].pos.x - g_lastblock[nCntLastBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_lastblock[nCntLastBlock].pos.x + g_lastblock[nCntLastBlock].vtxMax.x)
				{
					if (GetFade() == FADE_NONE)
					{//���Q�[���I�[�o�[
						pPlayer->bDisp = false;
						//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
						SetFade(MODE_GAMEOVER);
					}
				}
			}
		}
	}
}

//==============================================================
//�n�C�X�s�[�h�f�b�h�u���b�N�̎擾����
//==============================================================
LastBlock* GetLastBlock(void) 
{
	return &g_lastblock[MAX_LBLOCK];
}