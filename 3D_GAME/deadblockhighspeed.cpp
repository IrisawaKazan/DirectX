//==============================================================
//
//[deadblockhighspeed.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"deadblockhighspeed.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureDeadBlockHS[MAX_DEADHSBLOCK] = {};
DeadBlockHS g_deadblockhs[MAX_DEADHSBLOCK];

//==============================================================
//�n�C�X�s�[�h�f�b�h�u���b�N�̏���������
//==============================================================
void InitDeadBlockHS(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		g_deadblockhs[nCntDeadBlockHS].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_deadblockhs[nCntDeadBlockHS].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].pMesh = NULL;
		g_deadblockhs[nCntDeadBlockHS].pBuffMat = NULL;
		g_deadblockhs[nCntDeadBlockHS].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].dwNumMat = 0;
		g_deadblockhs[nCntDeadBlockHS].mtxWorld = {};
		g_deadblockhs[nCntDeadBlockHS].bUse = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\boxdeadhighspeed000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_deadblockhs[nCntDeadBlockHS].pBuffMat,
			NULL,
			&g_deadblockhs[nCntDeadBlockHS].dwNumMat,
			&g_deadblockhs[nCntDeadBlockHS].pMesh);

		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�̃|�C���^

		//���_���̎擾
		nNumVtx = g_deadblockhs[nCntDeadBlockHS].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_deadblockhs[nCntDeadBlockHS].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_deadblockhs[nCntDeadBlockHS].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l,�ő�l���擾
			if (vtx.x <= g_deadblockhs[nCntDeadBlockHS].vtxMin.x)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_deadblockhs[nCntDeadBlockHS].vtxMin.y)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_deadblockhs[nCntDeadBlockHS].vtxMin.z)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_deadblockhs[nCntDeadBlockHS].vtxMax.x)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_deadblockhs[nCntDeadBlockHS].vtxMax.y)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_deadblockhs[nCntDeadBlockHS].vtxMax.z)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_deadblockhs[nCntDeadBlockHS].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_deadblockhs[nCntDeadBlockHS].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_deadblockhs[nCntDeadBlockHS].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���


				//�e�N�X�`���̓ǂݍ���


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureDeadBlockHS[nCntMat]);
			}
		}
	}
}

//==============================================================
//�n�C�X�s�[�h�f�b�h�u���b�N�̏I������
//==============================================================
void UninitDeadBlockHS(void)
{
	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		//���b�V���̔j��
		if (g_deadblockhs[nCntDeadBlockHS].pMesh != NULL)
		{
			g_deadblockhs[nCntDeadBlockHS].pMesh->Release();
			g_deadblockhs[nCntDeadBlockHS].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_deadblockhs[nCntDeadBlockHS].pBuffMat != NULL)
		{
			g_deadblockhs[nCntDeadBlockHS].pBuffMat->Release();
			g_deadblockhs[nCntDeadBlockHS].pBuffMat = NULL;
		}
	}
}

//==============================================================
//�n�C�X�s�[�h�f�b�h�u���b�N�̍X�V����
//==============================================================
void UpdateDeadBlockHS(void)
{
	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == true)
		{
			if (g_deadblockhs[nCntDeadBlockHS].nType == 1)
			{
				//�E�ɓ���
				g_deadblockhs[nCntDeadBlockHS].pos.x += sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.x += cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
			if (g_deadblockhs[nCntDeadBlockHS].nType == 2)
			{
				//���ɓ���
				g_deadblockhs[nCntDeadBlockHS].pos.x -= sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.x -= cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
			if (g_deadblockhs[nCntDeadBlockHS].nType == 3)
			{
				//���ɓ���
				g_deadblockhs[nCntDeadBlockHS].pos.x += sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.z += cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
			if (g_deadblockhs[nCntDeadBlockHS].nType == 4)
			{
				//��O�ɓ���
				g_deadblockhs[nCntDeadBlockHS].pos.x -= sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.z -= cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//�n�C�X�s�[�h�f�b�h�u���b�N�̕`�揈��
//==============================================================
void DrawDeadBlockHS(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_deadblockhs[nCntDeadBlockHS].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_deadblockhs[nCntDeadBlockHS].rot.y, g_deadblockhs[nCntDeadBlockHS].rot.x, g_deadblockhs[nCntDeadBlockHS].rot.z);
			D3DXMatrixMultiply(&g_deadblockhs[nCntDeadBlockHS].mtxWorld, &g_deadblockhs[nCntDeadBlockHS].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_deadblockhs[nCntDeadBlockHS].pos.x, g_deadblockhs[nCntDeadBlockHS].pos.y, g_deadblockhs[nCntDeadBlockHS].pos.z);
			D3DXMatrixMultiply(&g_deadblockhs[nCntDeadBlockHS].mtxWorld, &g_deadblockhs[nCntDeadBlockHS].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_deadblockhs[nCntDeadBlockHS].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_deadblockhs[nCntDeadBlockHS].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_deadblockhs[nCntDeadBlockHS].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureDeadBlockHS[nCntMat]);//����NULL

				//���f��(�p�[�c)�̕`��
				g_deadblockhs[nCntDeadBlockHS].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A�������ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//�n�C�X�s�[�h�f�b�h�u���b�N�̐ݒ菈��
//==============================================================
void SetDeadBlockHS(D3DXVECTOR3 pos, int type)
{
	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == false)
		{//�u���b�N�̎g�p����Ă��Ȃ�
			g_deadblockhs[nCntDeadBlockHS].pos = pos;
			g_deadblockhs[nCntDeadBlockHS].nType = type;

			g_deadblockhs[nCntDeadBlockHS].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}

//==============================================================
//�n�C�X�s�[�h�f�b�h�u���b�N��X���̓����蔻�菈��
//==============================================================
void CollisionDeadBlockHSX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == true)
		{
			//���E�̂߂荞�ݔ���
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_deadblockhs[nCntDeadBlockHS].pos.z + g_deadblockhs[nCntDeadBlockHS].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_deadblockhs[nCntDeadBlockHS].pos.z - g_deadblockhs[nCntDeadBlockHS].vtxMin.z * 2.0f)
			{
				//������E��
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_deadblockhs[nCntDeadBlockHS].pos.x + g_deadblockhs[nCntDeadBlockHS].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_deadblockhs[nCntDeadBlockHS].pos.x - g_deadblockhs[nCntDeadBlockHS].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//���Q�[���I�[�o�[
						pPlayer->bDisp = false;
						//���[�h�ݒ�(�Q�[���I�[�o�[��ʂɈڍs)
						SetFade(MODE_GAMEOVER);
					}
				}
				//�E���獶��
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_deadblockhs[nCntDeadBlockHS].pos.x - g_deadblockhs[nCntDeadBlockHS].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_deadblockhs[nCntDeadBlockHS].pos.x + g_deadblockhs[nCntDeadBlockHS].vtxMax.x)
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
DeadBlockHS* GetDeadBlockHS(void)
{
	return &g_deadblockhs[MAX_DEADHSBLOCK];
}