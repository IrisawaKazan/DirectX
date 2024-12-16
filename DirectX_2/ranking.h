//==============================================================
//
//SHOOTING GAME[ranking.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//マクロ定義
#define MAX_RANK (5)//表示順位数

//プロトタイプ
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);

#endif