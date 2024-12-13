//==============================================================
//
//3D_GAME[meshfield.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include"main.h"

//�}�N����`
#define MAX_MFX (2)                                                           //��(X)�̎l�p�̐�
#define MAX_MFZ (2)                                                           //�c(Z)�̎l�p�̐�
#define MAX_MFPVTX ((MAX_MFX + 1) * (MAX_MFZ + 1))                            //���_��
#define MAX_MFPOLYGON (MAX_MFX * MAX_MFZ * 2 + (MAX_MFZ - 1) * 2 * MAX_MFZ)   //�|���S����
#define MAX_MFPIDX ((MAX_MFX + 1) * 2 * MAX_MFZ + (MAX_MFZ - 1) * 2 * MAX_MFZ)//�C���f�b�N�X��
#define MAX_MFPOS (150.0f)                                                    //�l�p��̑傫��

//���b�V���t�B�[���h�̍\���̂̒�`
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;     //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 pos;                 //�ʒu
	D3DXVECTOR3 rot;                 //����
	D3DXMATRIX mtxWorld;             //���[���h�}�g���b�N�X
}Meshfield;

//�v���g�^�C�v�錾
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif