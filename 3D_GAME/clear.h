//==============================================================
//
//3D_GAME[clear.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _CLEAR_H_
#define _CLEAR_H_

#include"main.h"
#include"input.h"
#include"fade.h"
#include"game.h"
#include"title.h"
#include"result.h"
#include"clearfirst.h"
#include"clearsecond.h"

//�N���A�̎��
typedef enum
{
	CLEAR_1 = 0,
	CLEAR_2,
	CLEAR_MAX
}CLEAR;

//�v���g�^�C�v�錾
void InitClear(void);
void UninitClear(void);
void UpdateClear(void);
void DrawClear(void);
void SetClear(CLEAR clear);
CLEAR GetClear(void);

#endif