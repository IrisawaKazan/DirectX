//==============================================================
//
//3D_GAME[cameracontroller.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"cameracontroller.h"

//�O���[�o���ϐ�
Cameracontroller g_cameracontroller;//�J�������

//==============================================================
//�J�����̏���������
//==============================================================
void InitCameracontroller(void)
{
	Player* pPlayer = GetPlayer();

	//���_,�����_,�������ݒ肷��
	g_cameracontroller.posV = D3DXVECTOR3(0.0f, 200.0f, -250.0f);
	g_cameracontroller.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_camera.posR = pPlayer->pos;
	g_cameracontroller.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_cameracontroller.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cameracontroller.fDistance = sqrtf((g_cameracontroller.posR.x - g_cameracontroller.posV.x) * (g_cameracontroller.posR.x - g_cameracontroller.posV.x) +
		(g_cameracontroller.posR.y - g_cameracontroller.posV.y) * (g_cameracontroller.posR.y - g_cameracontroller.posV.y) +
		(g_cameracontroller.posR.z - g_cameracontroller.posV.z) * (g_cameracontroller.posR.z - g_cameracontroller.posV.z));
}

//==============================================================
//�J�����̏I������
//==============================================================
void UninitCameracontroller(void)
{

}

//==============================================================
//�J�����̍X�V����
//==============================================================
void UpdateCameracontroller(void)
{
	Player* pPlayer = GetPlayer();

	//���_�̐���
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_cameracontroller.rot.y -= 0.02f;

		//�p�x�̐��K��
		if (-D3DX_PI > g_cameracontroller.rot.y)
		{
			g_cameracontroller.rot.y = g_cameracontroller.rot.y + D3DX_PI * 2.0f;
		}

		g_cameracontroller.posV.x = g_cameracontroller.posR.x - sinf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
		g_cameracontroller.posV.z = g_cameracontroller.posR.z - cosf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{
		g_cameracontroller.rot.y += 0.02f;
	
		//�p�x�̐��K��
		if (D3DX_PI < g_cameracontroller.rot.y)
		{
			g_cameracontroller.rot.y = g_cameracontroller.rot.y - D3DX_PI * 2.0f;
		}
	
		g_cameracontroller.posV.x = g_cameracontroller.posR.x - sinf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
		g_cameracontroller.posV.z = g_cameracontroller.posR.z - cosf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
	}
}

//==============================================================
//�J�����̐ݒ菈��
//==============================================================
void SetCameracontroller(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_cameracontroller.mtxView);

	D3DXMatrixLookAtLH(&g_cameracontroller.mtxView,
		&g_cameracontroller.posV,
		&g_cameracontroller.posR,
		&g_cameracontroller.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_cameracontroller.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_cameracontroller.mtxProjection);

	D3DXMatrixPerspectiveFovLH(&g_cameracontroller.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_cameracontroller.mtxProjection);
}

//==============================================================
//�J�����̎擾����
//==============================================================
Cameracontroller* GetCameracontroller(void)
{
	return &g_cameracontroller;
}