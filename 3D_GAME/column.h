//==============================================================
//
//3D_GAME[column.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _COLUMN_H_
#define _COLUMN_H_

#include"main.h"

//マクロ定義
#define MAX_CX (8)
#define MAX_CZ (1)
#define MAX_CPVTX ((MAX_CX + 1) * (MAX_CZ + 1))
#define MAX_CPOLYGON (MAX_CX * MAX_CZ * 2 + (MAX_CZ - 1) * 4)
#define MAX_CPIDX ((MAX_CX + 1) * 2 * MAX_CZ + (MAX_CZ - 1) * 2)
#define MAX_CPOS (150.0f)

//プロトタイプ宣言
void InitColumn(void);
void UninitColumn(void);
void UpdateColumn(void);
void DrawColumn(void);

#endif