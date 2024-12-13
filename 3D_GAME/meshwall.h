//==============================================================
//
//3D_GAME[meshwall.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include"main.h"

//�}�N����`
#define MAX_MWX (2)                                                           //��(X)�̎l�p�̐�
#define MAX_MWZ (2)                                                           //�c(Z)�̎l�p�̐�
#define MAX_MWPVTX ((MAX_MWX + 1) * (MAX_MWZ + 1))                            //���_��
#define MAX_MWPOLYGON (MAX_MWX * MAX_MWZ * 2 + (MAX_MWZ - 1) * 2 * MAX_MWZ)   //�|���S����
#define MAX_MWPIDX ((MAX_MWX + 1) * 2 * MAX_MWZ + (MAX_MWZ - 1) * 2 * MAX_MWZ)//�C���f�b�N�X��
#define NUM_PLUS (/*80*/0.0f)
#define MAX_MWPOSX (150.0f + NUM_PLUS)                                        //�ǂ�x
#define MAX_MWPOSZ (MAX_MWPOSX - NUM_PLUS)                                    //�ǂ�z
#define MAX_MWHEIGHT (700.0f)                                                 //�ǂ̍���

//���b�V���E�H�[���̍\���̂̒�`
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;     //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 pos;                 //�ʒu
	D3DXVECTOR3 rot;                 //����
	D3DXMATRIX mtxWorld;             //���[���h�}�g���b�N�X
}Meshwall;

//�v���g�^�C�v�錾
void InitMeshwall(void);
void UninitMeshwall(void);
void UpdateMeshwall(void);
void DrawMeshwall(void);

#endif