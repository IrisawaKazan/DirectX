//==============================================================
//
//3D_GAME[sphere.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include"main.h"

//�X�t�B�A�̍\����
typedef struct
{
	LPD3DXMESH pMesh;     //���b�V��(���_���W)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;       //�}�e���A���̐�
	int nIdxModelParant;  //�e���f���̃C���f�b�N�X
	D3DXVECTOR3 pos;      //�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;      //����
	D3DXMATRIX mtxWorld;  //���[���h�}�g���b�N�X
}Sphere;

//�v���g�^�C�v�錾
void InitSphere(void);
void UninitSphere(void);
void UpdateSphere(void);
void DrawSphere(void);

#endif