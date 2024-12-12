//==============================================================
//
//[player.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"
#include"block.h"
#include"model.h"
#include"deadblock.h"
#include"deadblockhighspeed.h"
#include"goalblock.h"
#include"lastblock.h"

//マクロ定義
#define MAX_PTEXTURE (128)
#define MAX_PMOVE (2.0f)
#define MAX_PARTS (2)
#define MAX_KEY (10)
#define MAX_MOTION (5)

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,//待機
	MOTIONTYPE_MOVE,       //移動
	MOTIONTYPE_ACTION,     //アクション
	MOTIONTYPE_JUMP,       //ジャンプ
	MOTIONTYPE_LANDING,    //着地
	MOTIONTYPE_MAX
}MOTIONTYPE;

//キー構造体
typedef struct
{
	float fPosX;//位置X
	float fPosY;//位置Y
	float fPosZ;//位置Z
	float fRotX;//向きX
	float fRotY;//向きY
	float fRotZ;//向きZ
}KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;         //再生フレーム
	KEY aKey[MAX_PARTS];//各パーツのキー要素
}KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;                //ループするかどうか
	int nNumKey;               //キーの総数
	KEY_INFO aKeyInfo[MAX_KEY];//キー情報
}MOTION_INFO;

//プレイヤーの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;                    //位置
	D3DXVECTOR3 posOld;                 //前回の位置
	D3DXVECTOR3 size;                   //大きさ
	D3DXVECTOR3 move;                   //移動量
	D3DXVECTOR3 rot;                    //向き
	D3DXVECTOR3 rotDest;                //目標の向き
	D3DXVECTOR3 vtxMin;                 //モデルの最小値
	D3DXVECTOR3 vtxMax;                 //モデルの最大値
	LPD3DXMESH pMesh;                   //メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER pBuffMat;              //マテリアルへのポインタ
	D3DXMATRIX mtxWorld;                //ワールドマトリックス
	DWORD dwNumMat;                     //マテリアルの数
	int nCounterState;                  //状態管理カウンター
	int nIdxShadow;	                    //影の番号
	bool bDisp;                         //表示するかしないか
	bool bJump;                         //ジャンプ中かどうか
	bool bRightMove;                    //右を向いているかどうか
	Model aModel[MAX_PARTS];            //モデル(パーツ)
	int nNumModel;                      //モデル(パーツ)の総数
	MOTION_INFO aMotionInfo[MAX_MOTION];//モーション情報
	int nNumMotion;                     //モーションの総数
	MOTIONTYPE motionType;              //モーションの種類
	bool bLoopMotion;                   //ループするかどうか
	int nNumKey;                        //キーの総数
	int nKey;                           //現在のキーNo.
	int nCounterMotion;                 //モーションのカウンター
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif