//==============================================================
//
//[block.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//�}�N����`
#define MAX_BLOCK (128)

//�u���b�N�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;      //�ʒu
	D3DXVECTOR3 rot;      //����
	D3DXVECTOR3 vtxMin;   //���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;   //���f���̍ő�l
	LPD3DXMESH pMesh;     //���b�V��(���_���W)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;       //�}�e���A���̐�
	D3DXMATRIX mtxWorld;  //���[���h�}�g���b�N�X
	bool bUse;            //�g���Ă��邩���Ȃ���
}Block;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos);
void CollisionBlockX(void);//X���̓����蔻��
void CollisionBlockZ(void);//Z���̓����蔻��

#endif