//==============================================================
//
//ACTION_GAME[player.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _PLAYER_H_//このマクロ定義がされてなかったら
#define _PLAYER_H_//2重インクルード防止のマクロ定義

#include"block.h"

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//出現状態
	PLAYERSTATE_NORMAL,    //通常
	PLAYERSTATE_DAMAGE,    //ダメージ
	PLAYERSTATE_DEATH,     //死亡
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤーの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;   //位置
	D3DXVECTOR3 posOld;//前回の位置
	D3DXVECTOR3 move;  //移動量
	PLAYERSTATE state; //プレイヤーの状態
	int nCounterState; //状態管理カウンター
	//int nLife;         //体力
	bool bDisp;        //表示するかしないか
	bool bJump;        //ジャンプ中かどうか
	bool bRightMove;   //右を向いているかどうか
	Block* pBlock;     //対象ブロックへのポインタ
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
Player* GetPlayer(void);

#endif