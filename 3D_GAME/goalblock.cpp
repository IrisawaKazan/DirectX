//==============================================================
//
//3D_GAME[goalblock.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"goalblock.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureGoalBlock[MAX_GBLOCK] = {};
GoalBlock g_goalblock[MAX_GBLOCK];

//==============================================================
//�S�[���u���b�N�̏���������
//==============================================================
void InitGoalBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		g_goalblock[nCntGoalBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_goalblock[nCntGoalBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].pMesh = NULL;
		g_goalblock[nCntGoalBlock].pBuffMat = NULL;
		g_goalblock[nCntGoalBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].dwNumMat = 0;
		g_goalblock[nCntGoalBlock].mtxWorld = {};
		g_goalblock[nCntGoalBlock].bUse = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\boxgoal000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_goalblock[nCntGoalBlock].pBuffMat,
			NULL,
			&g_goalblock[nCntGoalBlock].dwNumMat,
			&g_goalblock[nCntGoalBlock].pMesh);

		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�̃|�C���^

		//���_���̎擾
		nNumVtx = g_goalblock[nCntGoalBlock].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_goalblock[nCntGoalBlock].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_goalblock[nCntGoalBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l,�ő�l���擾
			if (vtx.x <= g_goalblock[nCntGoalBlock].vtxMin.x)
			{
				g_goalblock[nCntGoalBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_goalblock[nCntGoalBlock].vtxMin.y)
			{
				g_goalblock[nCntGoalBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_goalblock[nCntGoalBlock].vtxMin.z)
			{
				g_goalblock[nCntGoalBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_goalblock[nCntGoalBlock].vtxMax.x)
			{
				g_goalblock[nCntGoalBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_goalblock[nCntGoalBlock].vtxMax.y)
			{
				g_goalblock[nCntGoalBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_goalblock[nCntGoalBlock].vtxMax.z)
			{
				g_goalblock[nCntGoalBlock].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_goalblock[nCntGoalBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_goalblock[nCntGoalBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_goalblock[nCntGoalBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���


				//�e�N�X�`���̓ǂݍ���


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureGoalBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//�S�[���u���b�N�̏I������
//==============================================================
void UninitGoalBlock(void)
{
	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		//���b�V���̔j��
		if (g_goalblock[nCntGoalBlock].pMesh != NULL)
		{
			g_goalblock[nCntGoalBlock].pMesh->Release();
			g_goalblock[nCntGoalBlock].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_goalblock[nCntGoalBlock].pBuffMat != NULL)
		{
			g_goalblock[nCntGoalBlock].pBuffMat->Release();
			g_goalblock[nCntGoalBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//�S�[���u���b�N�̍X�V����
//==============================================================
void UpdateGoalBlock(void)
{
	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			if (g_goalblock[nCntGoalBlock].nType == 1)
			{
				//���ɓ���
				g_goalblock[nCntGoalBlock].pos.x += sinf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS1 / sqrtf(2.0f);
				g_goalblock[nCntGoalBlock].pos.z += cosf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS1 / sqrtf(2.0f);
			}
		}
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			if (g_goalblock[nCntGoalBlock].nType == 2)
			{
				//���ɓ���
				g_goalblock[nCntGoalBlock].pos.x += sinf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS2 / sqrtf(2.0f);
				g_goalblock[nCntGoalBlock].pos.z += cosf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS2 / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//�S�[���u���b�N�̕`�揈��
//==============================================================
void DrawGoalBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_goalblock[nCntGoalBlock].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goalblock[nCntGoalBlock].rot.y, g_goalblock[nCntGoalBlock].rot.x, g_goalblock[nCntGoalBlock].rot.z);
			D3DXMatrixMultiply(&g_goalblock[nCntGoalBlock].mtxWorld, &g_goalblock[nCntGoalBlock].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_goalblock[nCntGoalBlock].pos.x, g_goalblock[nCntGoalBlock].pos.y, g_goalblock[nCntGoalBlock].pos.z);
			D3DXMatrixMultiply(&g_goalblock[nCntGoalBlock].mtxWorld, &g_goalblock[nCntGoalBlock].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_goalblock[nCntGoalBlock].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_goalblock[nCntGoalBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_goalblock[nCntGoalBlock].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureGoalBlock[nCntMat]);//����NULL

				//���f��(�p�[�c)�̕`��
				g_goalblock[nCntGoalBlock].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A�������ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//�S�[���u���b�N�̐ݒ菈��
//==============================================================
void SetGoalBlock(D3DXVECTOR3 pos, int type)
{
	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == false)
		{//�u���b�N�̎g�p����Ă��Ȃ�
			g_goalblock[nCntGoalBlock].pos = pos;
			g_goalblock[nCntGoalBlock].nType = type;

			g_goalblock[nCntGoalBlock].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}

//==============================================================
//�S�[���u���b�N��X���̓����蔻�菈��
//==============================================================
void CollisionGoalBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			//���E�̂߂荞�ݔ���
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_goalblock[nCntGoalBlock].pos.z + g_goalblock[nCntGoalBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_goalblock[nCntGoalBlock].pos.z - g_goalblock[nCntGoalBlock].vtxMin.z * 2.0f)
			{
				//������E��
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_goalblock[nCntGoalBlock].pos.x + g_goalblock[nCntGoalBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_goalblock[nCntGoalBlock].pos.x - g_goalblock[nCntGoalBlock].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//�Q�[���I�[�o�[
						pPlayer->bDisp = false;
						//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
						SetFade(MODE_GAMEOVER);
					}
				}
				//�E���獶��
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_goalblock[nCntGoalBlock].pos.x - g_goalblock[nCntGoalBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_goalblock[nCntGoalBlock].pos.x + g_goalblock[nCntGoalBlock].vtxMax.x)
				{
					if (GetFade() == FADE_NONE)
					{//�Q�[���I�[�o�[
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
//�S�[���u���b�N�̎擾����
//==============================================================
GoalBlock* GetGoalBlock(void) 
{
	return &g_goalblock[MAX_GBLOCK];
}