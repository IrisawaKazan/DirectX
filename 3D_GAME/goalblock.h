//==============================================================
//
//[goalblock.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _GOALBLOCK_H_
#define _GOALBLOCK_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//�}�N����`
#define MAX_GBLOCK (128)
#define MAX_MGBLOCKS1 (0.1f)
#define MAX_MGBLOCKS2 (0.05f)

//�S�[���u���b�N�̍\���̂̒�`
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
	int nType;
}GoalBlock;

//�v���g�^�C�v�錾
void InitGoalBlock(void);
void UninitGoalBlock(void);
void UpdateGoalBlock(void);
void DrawGoalBlock(void);
void SetGoalBlock(D3DXVECTOR3 pos, int type);
void CollisionGoalBlockX(void);//X���̓����蔻��
GoalBlock* GetGoalBlock(void);

#endif