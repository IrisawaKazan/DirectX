//==============================================================
//
//[goal.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include"main.h"
#include"player.h"

//�}�N����`
#define MAX_GOAL (1)
#define GOAL_WIDTH (150.0f)
#define GOAL_HEIGHT (25.0f)

//�S�[���̍\����
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	D3DXVECTOR3 rot;    //����
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nType;
	bool bUse;
}Goal;

//�v���g�^�C�v�錾
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
int SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);

#endif