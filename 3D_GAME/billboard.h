//==============================================================
//
//3D_GAME[billboard.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include"main.h"

#define MAX_BILLBOARD (128)

//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	D3DXVECTOR3 rot;    //����
	D3DXVECTOR3 move;   //�ړ���
	//D3DXVECTOR3 dir;    //����
	//int nLife;          //����
	//int nType;          //���
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	bool bUse;          //���p���Ă��邩�ǂ���
}Billboard;

//�v���g�^�C�v�錾
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos/*, D3DXVECTOR3 move, D3DXVECTOR3 dir, int nLife*/);//�e�Ȃǂ��o�������Ƃ�

#endif