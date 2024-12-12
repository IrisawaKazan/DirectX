//==============================================================
//
//[deadblock.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"deadblock.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureDeadBlock[MAX_DEADBLOCK] = {};
DeadBlock g_deadblock[MAX_DEADBLOCK];

//==============================================================
//�f�b�h�u���b�N�̏���������
//==============================================================
void InitDeadBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		g_deadblock[nCntDeadBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_deadblock[nCntDeadBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].pMesh = NULL;
		g_deadblock[nCntDeadBlock].pBuffMat = NULL;
		g_deadblock[nCntDeadBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].dwNumMat = 0;
		g_deadblock[nCntDeadBlock].mtxWorld = {};
		g_deadblock[nCntDeadBlock].bUse = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\boxdead000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_deadblock[nCntDeadBlock].pBuffMat,
			NULL,
			&g_deadblock[nCntDeadBlock].dwNumMat,
			&g_deadblock[nCntDeadBlock].pMesh);

		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�̃|�C���^

		//���_���̎擾
		nNumVtx = g_deadblock[nCntDeadBlock].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_deadblock[nCntDeadBlock].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_deadblock[nCntDeadBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l,�ő�l���擾
			if (vtx.x <= g_deadblock[nCntDeadBlock].vtxMin.x)
			{
				g_deadblock[nCntDeadBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_deadblock[nCntDeadBlock].vtxMin.y)
			{
				g_deadblock[nCntDeadBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_deadblock[nCntDeadBlock].vtxMin.z)
			{
				g_deadblock[nCntDeadBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_deadblock[nCntDeadBlock].vtxMax.x)
			{
				g_deadblock[nCntDeadBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_deadblock[nCntDeadBlock].vtxMax.y)
			{
				g_deadblock[nCntDeadBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_deadblock[nCntDeadBlock].vtxMax.z)
			{
				g_deadblock[nCntDeadBlock].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_deadblock[nCntDeadBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_deadblock[nCntDeadBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_deadblock[nCntDeadBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���


				//�e�N�X�`���̓ǂݍ���


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureDeadBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//�f�b�h�u���b�N�̏I������
//==============================================================
void UninitDeadBlock(void)
{
	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		//���b�V���̔j��
		if (g_deadblock[nCntDeadBlock].pMesh != NULL)
		{
			g_deadblock[nCntDeadBlock].pMesh->Release();
			g_deadblock[nCntDeadBlock].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_deadblock[nCntDeadBlock].pBuffMat != NULL)
		{
			g_deadblock[nCntDeadBlock].pBuffMat->Release();
			g_deadblock[nCntDeadBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//�f�b�h�u���b�N�̍X�V����
//==============================================================
void UpdateDeadBlock(void)
{
	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == true)
		{
			if (g_deadblock[nCntDeadBlock].nType == 1)
			{
				//�E�ɓ���
				g_deadblock[nCntDeadBlock].pos.x += sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.x += cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
			if (g_deadblock[nCntDeadBlock].nType == 2)
			{
				//���ɓ���
				g_deadblock[nCntDeadBlock].pos.x -= sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.x -= cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
			if (g_deadblock[nCntDeadBlock].nType == 3)
			{
				//���ɓ���
				g_deadblock[nCntDeadBlock].pos.x += sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.z += cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
			if (g_deadblock[nCntDeadBlock].nType == 4)
			{
				//��O�ɓ���
				g_deadblock[nCntDeadBlock].pos.x -= sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.z -= cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//�f�b�h�u���b�N�̕`�揈��
//==============================================================
void DrawDeadBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_deadblock[nCntDeadBlock].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_deadblock[nCntDeadBlock].rot.y, g_deadblock[nCntDeadBlock].rot.x, g_deadblock[nCntDeadBlock].rot.z);
			D3DXMatrixMultiply(&g_deadblock[nCntDeadBlock].mtxWorld, &g_deadblock[nCntDeadBlock].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_deadblock[nCntDeadBlock].pos.x, g_deadblock[nCntDeadBlock].pos.y, g_deadblock[nCntDeadBlock].pos.z);
			D3DXMatrixMultiply(&g_deadblock[nCntDeadBlock].mtxWorld, &g_deadblock[nCntDeadBlock].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_deadblock[nCntDeadBlock].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_deadblock[nCntDeadBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_deadblock[nCntDeadBlock].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureDeadBlock[nCntMat]);//����NULL

				//���f��(�p�[�c)�̕`��
				g_deadblock[nCntDeadBlock].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A�������ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//�f�b�h�u���b�N�̐ݒ菈��
//==============================================================
void SetDeadBlock(D3DXVECTOR3 pos, int type)
{
	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == false)
		{//�u���b�N�̎g�p����Ă��Ȃ�
			g_deadblock[nCntDeadBlock].pos = pos;
			g_deadblock[nCntDeadBlock].nType = type;

			g_deadblock[nCntDeadBlock].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}

//==============================================================
//�f�b�h�u���b�N��X���̓����蔻�菈��
//==============================================================
void CollisionDeadBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == true)
		{
			//���E�̂߂荞�ݔ���
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_deadblock[nCntDeadBlock].pos.z + g_deadblock[nCntDeadBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_deadblock[nCntDeadBlock].pos.z - g_deadblock[nCntDeadBlock].vtxMin.z * 2.0f)
			{
				//������E��
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_deadblock[nCntDeadBlock].pos.x + g_deadblock[nCntDeadBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_deadblock[nCntDeadBlock].pos.x - g_deadblock[nCntDeadBlock].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//���Q�[���I�[�o�[
						pPlayer->bDisp = false;
						//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
						SetFade(MODE_GAMEOVER);
					}
				}
				//�E���獶��
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_deadblock[nCntDeadBlock].pos.x - g_deadblock[nCntDeadBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_deadblock[nCntDeadBlock].pos.x + g_deadblock[nCntDeadBlock].vtxMax.x)
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
//�f�b�h�u���b�N�̎擾����
//==============================================================
DeadBlock* GetDeadBlock(void)
{
	return &g_deadblock[MAX_DEADBLOCK];
}