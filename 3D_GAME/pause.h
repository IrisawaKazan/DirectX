//==============================================================
//
//[pause.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"main.h"
#include"game.h"
#include"player.h"
#include"input.h"
#include"fade.h"
#include"camera.h"

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,       //�Q�[������蒼��
	PAUSE_MENU_QUIT,        //�^�C�g����ʂɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif