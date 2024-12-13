//==============================================================
//
//[deadblockhighspeed.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _DEADBLOCKHS_H_
#define _DEADBLOCKHS_H_

#include"main.h"
#include"player.h"
#include"fade.h"

//�}�N����`
#define MAX_DEADHSBLOCK (256)
#define MAX_MDHSBLOCK (3.0f)

//�n�C�X�s�[�h�f�b�h�u���b�N�̍\���̂̒�`
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
}DeadBlockHS;

//�v���g�^�C�v�錾
void InitDeadBlockHS(void);
void UninitDeadBlockHS(void);
void UpdateDeadBlockHS(void);
void DrawDeadBlockHS(void);
void SetDeadBlockHS(D3DXVECTOR3 pos, int type);
void CollisionDeadBlockHSX(void);//X���̓����蔻��
DeadBlockHS* GetDeadBlockHS(void);

#endif