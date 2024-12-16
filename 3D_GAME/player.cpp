//==============================================================
//
//3D_GAME[player.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_PTEXTURE] = {};
Player g_player;

//==============================================================
//�v���C���[�̏���������
//==============================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, -140.0f);
	//g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.pMesh = NULL;
	//g_player.pBuffMat = NULL;
	//g_player.dwNumMat = 0;
	//g_player.mtxWorld = {};
	//g_player.aModel->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.aModel->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\00_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].dwNumMat,
		&g_player.aModel[0].pMesh);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\01_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,
		NULL,
		&g_player.aModel[1].dwNumMat,
		&g_player.aModel[1].pMesh);

	//�p�[�c�̑���
	g_player.nNumModel = MAX_PARTS;

	//�e�p�[�c���̊K�w�\���ݒ�
	g_player.aModel[0].nIdxModelParant = -1;               //�e���f���̃C���f�b�N�X�̐ݒ�
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu�̏������ݒ�
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏������ݒ�

	g_player.aModel[1].nIdxModelParant = 0;                 //�e���f���̃C���f�b�N�X�̐ݒ�
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 17.5f, 0.0f);//�ʒu�̏������ݒ�
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏������ݒ�

	int nNumVtx;   //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�̃|�C���^

	//���_���̎擾
	nNumVtx = g_player.aModel[0].pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_player.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���_���W���r���ă��f���̍ŏ��l,�ő�l���擾
		if (vtx.x <= g_player.vtxMin.x)
		{
			g_player.vtxMin.x = vtx.x;
		}

		if (vtx.y <= g_player.vtxMin.y)
		{
			g_player.vtxMin.y = vtx.y;
		}

		if (vtx.z <= g_player.vtxMin.z)
		{
			g_player.vtxMin.z = vtx.z;
		}

		if (vtx.x >= g_player.vtxMax.x)
		{
			g_player.vtxMax.x = vtx.x;
		}

		if (vtx.y >= g_player.vtxMax.y)
		{
			g_player.vtxMax.y = vtx.y;
		}

		if (vtx.z >= g_player.vtxMax.z)
		{
			g_player.vtxMax.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	g_player.size = D3DXVECTOR3(g_player.vtxMax.x - g_player.vtxMin.x, g_player.vtxMax.y - g_player.vtxMin.y, g_player.vtxMax.z - g_player.vtxMin.z);

	g_player.bDisp = true;

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_player.aModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_player.aModel->dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���


			//�e�N�X�`���̓ǂݍ���


			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTexturePlayer[nCntMat]);
		}
	}

	g_player.nIdxShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//==============================================================
//�v���C���[�̏I������
//==============================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		//���b�V���̔j��
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//==============================================================
//�v���C���[�̍X�V����
//==============================================================
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();

	//�u���b�N�Ƃ̓����蔻��
	{
		CollisionBlockX();
		CollisionBlockZ();
		CollisionDeadBlockX();
		CollisionDeadBlockHSX();
		CollisionGoalBlockX();
		CollisionLastBlockX();
	}

	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	//�v���C���[�ړ�
	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//��
			if (GetKeyboardPress(DIK_W) == true)
			{//�����Ɉړ�
				//��
				g_player.pos.x -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//��
				g_player.pos.x += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//����O�Ɉړ�
				//��
				g_player.pos.x -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//��O
				g_player.pos.x -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else
			{//���Ɉړ�
				g_player.pos.x -= cosf(pCamera->rot.y) * MAX_PMOVE;
				g_player.pos.z += sinf(pCamera->rot.y) * MAX_PMOVE;
				g_player.rot.y = g_player.rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//�E
			if (GetKeyboardPress(DIK_W) == true)
			{//�E�Ɉړ�
				//�E
				g_player.pos.x += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//��
				g_player.pos.x += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�E��O�Ɉړ�
				//�E
				g_player.pos.x += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//��O
				g_player.pos.x -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else
			{//�E�Ɉړ�
				g_player.pos.x += cosf(pCamera->rot.y) * MAX_PMOVE;
				g_player.pos.z -= sinf(pCamera->rot.y) * MAX_PMOVE;
				g_player.rot.y = g_player.rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//��
			g_player.pos.x += sinf(pCamera->rot.y) * MAX_PMOVE;
			g_player.pos.z += cosf(pCamera->rot.y) * MAX_PMOVE;
			g_player.rot.y = g_player.rot.y;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//��O
			g_player.pos.x -= sinf(pCamera->rot.y) * MAX_PMOVE;
			g_player.pos.z -= cosf(pCamera->rot.y) * MAX_PMOVE;
			g_player.rot.y = g_player.rot.y;
		}
	}

	//�S���f��(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		//�L�[��񂩂�ʒu,�������Z�o


		//�p�[�c�̈ʒu,������ݒ�
		g_player.aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f + nCntModel * 17.5f, 0.0f);
		g_player.aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_player.nCounterMotion++;

	SetPositionShadow(g_player.nIdxShadow, g_player.pos);
}

//==============================================================
//�v���C���[�̕`�揈��
//==============================================================
void DrawPlayer(void)
{
	if (g_player.bDisp == true)
	{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		pDevice = GetDevice();

		//�v�Z�p�̃}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;

		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

		D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.x, g_player.rot.y, g_player.rot.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�S�p�[�c�̕`��
		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;                 //�e�̃}�g���b�N�X

			//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
			if (g_player.aModel[nCntModel].nIdxModelParant != -1)
			{//�e���f��������ꍇ
				mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParant].mtxWorld;
			}
			else
			{//�e���f�����Ȃ��ꍇ
				mtxParent = g_player.mtxWorld;
			}

			//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
				&g_player.aModel[nCntModel].mtxWorld,
				&mtxParent);

			//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_player.aModel[nCntModel].mtxWorld);

			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);//����NULL

				//���f��(�p�[�c)�̕`��
				g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A�������ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==============================================================
//�v���C���[�̎擾����
//==============================================================
Player* GetPlayer(void)
{
	return &g_player;
}