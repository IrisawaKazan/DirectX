//==============================================================
//
//SHOOTING GAME[ranking.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//�}�N����`
#define MAX_RANK (5)//�\�����ʐ�

//�v���g�^�C�v
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);

#endif