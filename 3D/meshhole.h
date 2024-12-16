//==============================================================
//
//[meshhole.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MESHHOLE_H_
#define _MESHHOLE_H_

#include"main.h"

//�}�N����`
#define MAX_MHX (8)                                                           //��(X)�̎l�p�̐�
#define MAX_MHZ (1)                                                           //�c(Z)�̎l�p�̐�
#define MAX_MHPVTX ((MAX_MHX + 1) * (MAX_MHZ + 1))                            //���_��
#define MAX_MHPOLYGON (MAX_MHX * MAX_MHZ * 2 + (MAX_MHZ - 1) * 2 * MAX_MHZ)   //�|���S����
#define MAX_MHPIDX ((MAX_MHX + 1) * 2 * MAX_MHZ + (MAX_MHZ - 1) * 2 * MAX_MHZ)//�C���f�b�N�X��
#define MAX_MHPOS (10.0f)                                                     //��
#define MAX_MHHEIGHT (50.0f)                                                  //����
#define MAX_MHZ (25.0f)                                                       //���s

//���b�V���z�[���̍\���̂̒�`
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;     //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 pos;                 //�ʒu
	D3DXVECTOR3 rot;                 //����
	D3DXMATRIX mtxWorld;             //���[���h�}�g���b�N�X
}Meshhole;

//�v���g�^�C�v�錾
void InitMeshhole(void);
void UninitMeshhole(void);
void UpdateMeshhole(void);
void DrawMeshhole(void);

#endif