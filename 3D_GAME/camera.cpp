//==============================================================
//
//3D_GAME[camera.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"camera.h"

//�O���[�o���ϐ�
Camera g_camera;//�J�������

//==============================================================
//�J�����̏���������
//==============================================================
void InitCamera(void)
{
	Player* pPlayer = GetPlayer();

	//���_,�����_,�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -250.0f);//�ǂ�����
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_camera.posR = pPlayer->pos;
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x) +
		(g_camera.posR.y - g_camera.posV.y) * (g_camera.posR.y - g_camera.posV.y) +
		(g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z));
}

//==============================================================
//�J�����̏I������
//==============================================================
void UninitCamera(void)
{

}

//==============================================================
//�J�����̍X�V����
//==============================================================
void UpdateCamera(void)
{
	Player* pPlayer = GetPlayer();

	//�J�����̒Ǐ]
	g_camera.posRDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posRDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	g_camera.posV.x = pPlayer->pos.x;

	g_camera.posR.x += (pPlayer->pos.x - g_camera.posR.x) * 0.1f;
	g_camera.posR.z += (pPlayer->pos.z - g_camera.posR.z) * 0.1f;

	////�����_�̐���
	//if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_camera.rot.y -= 0.02f;

	//	//�p�x�̐��K��
	//	if (-D3DX_PI > g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
	//	}

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
	//else if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_camera.rot.y += 0.02f;
	//
	//	//�p�x�̐��K��
	//	if (D3DX_PI < g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
	//	}
	//
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}

	////���_�̐���
	//if (GetKeyboardPress(DIK_Z) == true)
	//{
	//	g_camera.rot.y -= 0.02f;

	//	//�p�x�̐��K��
	//	if (-D3DX_PI > g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
	//	}

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
	//else if (GetKeyboardPress(DIK_C) == true)
	//{
	//	g_camera.rot.y += 0.02f;
	//
	//	//�p�x�̐��K��
	//	if (D3DX_PI < g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
	//	}
	//
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	//}

	////�J�����̈ړ�
	//if (GetKeyboardPress(DIK_LEFT) == true)
	//{//��
	//	if (GetKeyboardPress(DIK_UP) == true)
	//	{//����Ɉړ�
	//		//��
	//		g_camera.posV.x -= cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//��
	//		g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN) == true)
	//	{//�����Ɉړ�
	//		//��
	//		g_camera.posV.x -= cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//��
	//		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else
	//	{//���Ɉړ�
	//		g_camera.posV.x -= cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_RIGHT) == true)
	//{//�E
	//	if (GetKeyboardPress(DIK_UP) == true)
	//	{//�E��Ɉړ�
	//		//�E
	//		g_camera.posV.x += cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//��
	//		g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN) == true)
	//	{//�E���Ɉړ�
	//		//�E
	//		g_camera.posV.x += cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//��
	//		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else
	//	{//�E�Ɉړ�
	//		g_camera.posV.x += cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_UP) == true)
	//{//��
	//	g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
	//	g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
	//else if (GetKeyboardPress(DIK_DOWN) == true)
	//{//��
	//	g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
	//	g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
}

//==============================================================
//�J�����̐ݒ菈��
//==============================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//==============================================================
//�J�����̎擾����
//==============================================================
Camera* GetCamera(void)
{
	return &g_camera;
}