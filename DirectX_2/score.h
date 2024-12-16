//==============================================================
//
//SHOOTING GAME[score.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nVslue);
int GetScore(void);

#endif