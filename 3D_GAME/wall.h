//==============================================================
//
//[wall.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"
#include"player.h"

//�}�N����`
#define MAX_WALL (128)
#define WALL_WIDTH (250.0f)
#define WALL_HEIGHT (100.0f)

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	D3DXVECTOR3 rot;    //����
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nType;
	bool bUse;
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
int SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);
void CollisionWall(void);

#endif