//==============================================================
//
//3D_GAME[deadblock.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _DEADBLOCK_H_
#define _DEADBLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"
#include"explosion.h"

//�}�N����`
#define MAX_DEADBLOCK (256)
#define MAX_MDBLOCK (1.5f)

//�f�b�h�u���b�N�̍\���̂̒�`
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
}DeadBlock;

//�v���g�^�C�v�錾
void InitDeadBlock(void);
void UninitDeadBlock(void);
void UpdateDeadBlock(void);
void DrawDeadBlock(void);
void SetDeadBlock(D3DXVECTOR3 pos, int type);
void CollisionDeadBlockX(void);//X���̓����蔻��
DeadBlock* GetDeadBlock(void);

#endif