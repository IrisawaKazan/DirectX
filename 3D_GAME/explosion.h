//==============================================================
//
//3D_GAME[explosion.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"main.h"
#include"bullet.h"
#include"player.h"

//�}�N����`
#define MAX_EXPLOSION (MAX_BULLET)//�����̍ő吔

//�����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	D3DXVECTOR3 col;    //�F
	D3DXVECTOR3 move;   //�ړ���
	int nCounterAnim;   //�A�j���[�V�����J�E���^�[
	int nPatternAnim;   //�A�j���[�V�����p�^�[��No.
	bool bUse;          //�g�p���Ă��邩�ǂ���
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif