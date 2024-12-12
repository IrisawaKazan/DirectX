//==============================================================
//
//[block.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"block.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBlock[MAX_BLOCK] = {};
Block g_block[MAX_BLOCK];

//==============================================================
//�u���b�N�̏���������
//==============================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_block[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_block[nCntBlock].pMesh = NULL;
		g_block[nCntBlock].pBuffMat = NULL;
		g_block[nCntBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_block[nCntBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_block[nCntBlock].dwNumMat = 0;
		g_block[nCntBlock].mtxWorld = {};
		g_block[nCntBlock].bUse = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\box100.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_block[nCntBlock].pBuffMat,
			NULL,
			&g_block[nCntBlock].dwNumMat,
			&g_block[nCntBlock].pMesh);

		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�̃|�C���^

		//���_���̎擾
		nNumVtx = g_block[nCntBlock].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_block[nCntBlock].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_block[nCntBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l,�ő�l���擾
			if (vtx.x <= g_block[nCntBlock].vtxMin.x)
			{
				g_block[nCntBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_block[nCntBlock].vtxMin.y)
			{
				g_block[nCntBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_block[nCntBlock].vtxMin.z)
			{
				g_block[nCntBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_block[nCntBlock].vtxMax.x)
			{
				g_block[nCntBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_block[nCntBlock].vtxMax.y)
			{
				g_block[nCntBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_block[nCntBlock].vtxMax.z)
			{
				g_block[nCntBlock].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_block[nCntBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_block[nCntBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_block[nCntBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���


				//�e�N�X�`���̓ǂݍ���


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//�u���b�N�̏I������
//==============================================================
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���b�V���̔j��
		if (g_block[nCntBlock].pMesh != NULL)
		{
			g_block[nCntBlock].pMesh->Release();
			g_block[nCntBlock].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_block[nCntBlock].pBuffMat != NULL)
		{
			g_block[nCntBlock].pBuffMat->Release();
			g_block[nCntBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//�u���b�N�̍X�V����
//==============================================================
void UpdateBlock(void)
{

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			////��O�ɓ���(Deadblock�p)
			//g_block[nCntBlock].pos.x -= sinf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			//g_block[nCntBlock].pos.z -= cosf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			
			////�E�ɓ���
			//g_block[nCntBlock].pos.x += sinf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			//g_block[nCntBlock].pos.x += cosf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);

			////���ɓ���
			//g_block[nCntBlock].pos.x -= sinf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			//g_block[nCntBlock].pos.x -= cosf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
		}
	}
}

//==============================================================
//�u���b�N�̕`�揈��
//==============================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_block[nCntBlock].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_block[nCntBlock].rot.y, g_block[nCntBlock].rot.x, g_block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_block[nCntBlock].mtxWorld, &g_block[nCntBlock].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_block[nCntBlock].mtxWorld, &g_block[nCntBlock].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_block[nCntBlock].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_block[nCntBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_block[nCntBlock].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);//����NULL

				//���f��(�p�[�c)�̕`��
				g_block[nCntBlock].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A�������ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//�u���b�N�̐ݒ菈��
//==============================================================
void SetBlock(D3DXVECTOR3 pos)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == false)
		{//�u���b�N�̎g�p����Ă��Ȃ�
			g_block[nCntBlock].pos = pos;

			g_block[nCntBlock].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}

//==============================================================
//�u���b�N��X���̓����蔻�菈��
//==============================================================
void CollisionBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			//���E�̂߂荞�ݔ���
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_block[nCntBlock].pos.z + g_block[nCntBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_block[nCntBlock].pos.z - g_block[nCntBlock].vtxMin.z * 2.0f)
			{
				//������E��
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_block[nCntBlock].pos.x + g_block[nCntBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_block[nCntBlock].pos.x - g_block[nCntBlock].vtxMin.x)
				{
					//pPlayer->pPos�����f���̍����ɂ�������
					pPlayer->pos.x = pPlayer->pos.x / 2.0f + g_block[nCntBlock].pos.x / 2.0f - pPlayer->size.x + g_block[nCntBlock].pos.x / 2.0f + g_block[nCntBlock].vtxMin.x / 2.0f - pPlayer->posOld.x / 2.0f;
					pPlayer->move.x = 0.0f;
				}
				//�E���獶��
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_block[nCntBlock].pos.x - g_block[nCntBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_block[nCntBlock].pos.x + g_block[nCntBlock].vtxMax.x)
				{
					//pPlayer->pPos�����f���̉E���ɂ�������
					pPlayer->pos.x = g_block[nCntBlock].pos.x / 2.0f - g_block[nCntBlock].pos.x / 2.0f - pPlayer->size.x / 2.0f - g_block[nCntBlock].vtxMin.x / 2.0f + pPlayer->posOld.x;
					pPlayer->move.x = 0.0f;
				}
			}
		}
	}
}

//==============================================================
//�u���b�N��Z���̓����蔻�菈��
//==============================================================
void CollisionBlockZ(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			////���s�̂߂荞�ݔ���
			//if (pPlayer->pos.x + pPlayer->size.x / 2.0f > g_block[nCntBlock].pos.x + g_block[nCntBlock].vtxMax.x &&
			//	pPlayer->pos.x + pPlayer->size.x / 2.0f < g_block[nCntBlock].pos.x - g_block[nCntBlock].vtxMin.x * 2.0f)
			//{
			//	//�������O��


			//	//��O���牜��

			//}
		}
	}
}