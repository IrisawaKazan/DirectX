//==============================================================
//
//3D_GAME[bullet.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

#define MAX_BULLET (32)

//�o���b�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	D3DXVECTOR3 rot;    //����
	D3DXVECTOR3 move;   //�ړ���
	D3DXVECTOR3 dir;    //����
	int nLife;          //����
	int nType;          //���
	int nIdxShadow;     //�e�̔ԍ�
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	bool bUse;          //���p���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 dir, int nLife);//�e�Ȃǂ��o�������Ƃ�

#endif