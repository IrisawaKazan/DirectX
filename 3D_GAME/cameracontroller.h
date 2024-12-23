//==============================================================
//
//3D_GAME[cameracontroller.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _CAMERACONTROLLER_H_
#define _CAMERACONTROLLER_H_

#include"main.h"
#include"input.h"
#include"player.h"

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
}Cameracontroller;

//�v���g�^�C�v�錾
void InitCameracontroller(void);
void UninitCameracontroller(void);
void UpdateCameracontroller(void);
void SetCameracontroller(void);
Cameracontroller* GetCameracontroller(void);

#endif