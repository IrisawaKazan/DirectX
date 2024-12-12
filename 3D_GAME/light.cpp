//==============================================================
//
//[light.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"light.h"

D3DLIGHT9 g_light[MAX_LIGHT];//���C�g���

//==============================================================
//���C�g�̏���������
//==============================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	D3DXVECTOR3 vecDir;//���C�g�̕����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&g_light, sizeof(g_light));

	//=========
	//���C�g0
	//=========
	//���C�g0�̏���ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g0�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g0�̕�����ݒ�
	vecDir = D3DXVECTOR3(1.5f, -1.5f, -1.5f);

	//���K������(�傫���ʒu�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[0].Direction = vecDir;

	//���C�g0�̐ݒ������
	pDevice->SetLight(0, &g_light[0]);

	//���C�g0��L���ɂ���(ON,OFF)
	pDevice->LightEnable(0, TRUE);

	//=========
	//���C�g1
	//=========
	//���C�g1�̏���ݒ�
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g1�̊g�U����ݒ�
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g1�̕�����ݒ�
	vecDir = D3DXVECTOR3(-1.5f, -1.5f, 1.5f);

	//���K������(�傫���ʒu�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[1].Direction = vecDir;

	//���C�g1�̐ݒ������
	pDevice->SetLight(1, &g_light[1]);

	//���C�g1��L���ɂ���(ON,OFF)
	pDevice->LightEnable(1, TRUE);
}

//==============================================================
//���C�g�̏I������
//==============================================================
void UninitLight(void)
{

}

//==============================================================
//���C�g�̍X�V����
//==============================================================
void UpdateLight(void)
{

}