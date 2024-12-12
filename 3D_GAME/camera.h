//==============================================================
//
//[camera.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

typedef struct
{
	D3DXVECTOR3 posV;        //視点
	D3DXVECTOR3 posR;        //注視点
	D3DXVECTOR3 posVDest;    //目標の視点
	D3DXVECTOR3 posRDest;    //目標の注視点
	D3DXVECTOR3 vecU;        //上方向ベクトル
	D3DXMATRIX mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX mtxView;      //ビューマトリックス
	D3DXVECTOR3 rot;         //向き(角度)
	float fDistance;         //視点から注視点までの距離
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera* GetCamera(void);

#endif