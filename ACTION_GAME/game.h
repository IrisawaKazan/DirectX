//==============================================================
//
//ACTION_GAME[game.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _GAME_H_
#define _GAME_H_

#include"main.h"

//�X�e�[�W�̎��
typedef enum
{
	STAGE_1 = 0,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_MAX
}STAGE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetEnablePause(bool bPause);
void SetStage(STAGE stage);
STAGE GetStage(void);

#endif