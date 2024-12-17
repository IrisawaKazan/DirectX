//==============================================================
//
//3D_GAME[sphere.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"sphere.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureSphere[1] = {};
Sphere g_sphere;

//==============================================================
//���f���̏���������
//==============================================================
void InitSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	g_sphere.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sphere.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sphere.pMesh = NULL;
	g_sphere.pBuffMat = NULL;
	g_sphere.dwNumMat = 0;
	g_sphere.mtxWorld = {};

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\sphere.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_sphere.pBuffMat,
		NULL,
		&g_sphere.dwNumMat,
		&g_sphere.pMesh);

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_sphere.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_sphere.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���


			//�e�N�X�`���̓ǂݍ���


			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureSphere[nCntMat]);
		}
	}
}

//==============================================================
//���f���̏I������
//==============================================================
void UninitSphere(void)
{
	//���b�V���̔j��
	if (g_sphere.pMesh != NULL)
	{
		g_sphere.pMesh->Release();
		g_sphere.pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (g_sphere.pBuffMat != NULL)
	{
		g_sphere.pBuffMat->Release();
		g_sphere.pBuffMat = NULL;
	}
}

//==============================================================
//���f���̍X�V����
//==============================================================
void UpdateSphere(void)
{

}

//==============================================================
//���f���̕`�揈��
//==============================================================
void DrawSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_sphere.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_sphere.rot.y, g_sphere.rot.x, g_sphere.rot.z);
	D3DXMatrixMultiply(&g_sphere.mtxWorld, &g_sphere.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_sphere.pos.x, g_sphere.pos.y, g_sphere.pos.z);
	D3DXMatrixMultiply(&g_sphere.mtxWorld, &g_sphere.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_sphere.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_sphere.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_sphere.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureSphere[nCntMat]);//����NULL

		//���f��(�p�[�c)�̕`��
		g_sphere.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}