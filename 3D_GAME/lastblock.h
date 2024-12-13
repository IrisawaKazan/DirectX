//==============================================================
//
//3D_GAME[lastblock.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _LASTBLOCK_H_
#define _LASTBLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//�}�N����`
#define MAX_LBLOCK (128)
#define MAX_MLBLOCK (1.0f)

//���X�g�u���b�N�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;      //�ʒu
	D3DXVECTOR3 rot;      //����
	D3DXVECTOR3 move;     //�ړ���
	D3DXVECTOR3 vtxMin;   //���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;   //���f���̍ő�l
	LPD3DXMESH pMesh;     //���b�V��(���_���W)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;       //�}�e���A���̐�
	D3DXMATRIX mtxWorld;  //���[���h�}�g���b�N�X
	bool bUse;            //�g���Ă��邩���Ȃ���
	int nType;            //���
}LastBlock;

//�v���g�^�C�v�錾
void InitLastBlock(void);
void UninitLastBlock(void);
void UpdateLastBlock(void);
void DrawLastBlock(void);
void SetLastBlock(D3DXVECTOR3 pos, int type);
void CollisionLastBlockX(void);//X���̓����蔻��
LastBlock* GetLastBlock(void);

#endif