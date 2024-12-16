//==============================================================
//
//SHOOTING GAME[enemy.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"

//�}�N����`
#define MAX_ENEMY (128)//�G�̍ő吔

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;
	int nType;      //���
	bool bUse;      //�g�p���Ă��邩�ǂ���
	int nLife;
	int g_shotcounter;
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type);
Enemy* GetEnemy(void);

#endif