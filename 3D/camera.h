//==============================================================
//
//[camera.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

typedef struct
{
	D3DXVECTOR3 posV;        //���_
	D3DXVECTOR3 posR;        //�����_
	D3DXVECTOR3 posVDest;    //�ڕW�̎��_
	D3DXVECTOR3 posRDest;    //�ڕW�̒����_
	D3DXVECTOR3 vecU;        //������x�N�g��
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;      //�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;         //����(�p�x)
	float fDistance;         //���_���璍���_�܂ł̋���
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera* GetCamera(void);

#endif