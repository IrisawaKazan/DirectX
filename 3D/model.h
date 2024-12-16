//==============================================================
//
//[model.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include"main.h"

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;     //���b�V��(���_���W)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;       //�}�e���A���̐�
	int nIdxModelParant;  //�e���f���̃C���f�b�N�X
	D3DXVECTOR3 pos;      //�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;      //����
	D3DXMATRIX mtxWorld;  //���[���h�}�g���b�N�X
}Model;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

#endif