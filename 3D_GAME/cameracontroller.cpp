//==============================================================
//
//3D_GAME[cameracontroller.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"cameracontroller.h"

//グローバル変数
Cameracontroller g_cameracontroller;//カメラ情報

//==============================================================
//カメラの初期化処理
//==============================================================
void InitCameracontroller(void)
{
	Player* pPlayer = GetPlayer();

	//視点,注視点,上方向を設定する
	g_cameracontroller.posV = D3DXVECTOR3(0.0f, 200.0f, -250.0f);
	g_cameracontroller.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_camera.posR = pPlayer->pos;
	g_cameracontroller.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_cameracontroller.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cameracontroller.fDistance = sqrtf((g_cameracontroller.posR.x - g_cameracontroller.posV.x) * (g_cameracontroller.posR.x - g_cameracontroller.posV.x) +
		(g_cameracontroller.posR.y - g_cameracontroller.posV.y) * (g_cameracontroller.posR.y - g_cameracontroller.posV.y) +
		(g_cameracontroller.posR.z - g_cameracontroller.posV.z) * (g_cameracontroller.posR.z - g_cameracontroller.posV.z));
}

//==============================================================
//カメラの終了処理
//==============================================================
void UninitCameracontroller(void)
{

}

//==============================================================
//カメラの更新処理
//==============================================================
void UpdateCameracontroller(void)
{
	Player* pPlayer = GetPlayer();

	//視点の旋回
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_cameracontroller.rot.y -= 0.02f;

		//角度の正規化
		if (-D3DX_PI > g_cameracontroller.rot.y)
		{
			g_cameracontroller.rot.y = g_cameracontroller.rot.y + D3DX_PI * 2.0f;
		}

		g_cameracontroller.posV.x = g_cameracontroller.posR.x - sinf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
		g_cameracontroller.posV.z = g_cameracontroller.posR.z - cosf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{
		g_cameracontroller.rot.y += 0.02f;
	
		//角度の正規化
		if (D3DX_PI < g_cameracontroller.rot.y)
		{
			g_cameracontroller.rot.y = g_cameracontroller.rot.y - D3DX_PI * 2.0f;
		}
	
		g_cameracontroller.posV.x = g_cameracontroller.posR.x - sinf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
		g_cameracontroller.posV.z = g_cameracontroller.posR.z - cosf(g_cameracontroller.rot.y) * g_cameracontroller.fDistance;
	}
}

//==============================================================
//カメラの設定処理
//==============================================================
void SetCameracontroller(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_cameracontroller.mtxView);

	D3DXMatrixLookAtLH(&g_cameracontroller.mtxView,
		&g_cameracontroller.posV,
		&g_cameracontroller.posR,
		&g_cameracontroller.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_cameracontroller.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_cameracontroller.mtxProjection);

	D3DXMatrixPerspectiveFovLH(&g_cameracontroller.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_cameracontroller.mtxProjection);
}

//==============================================================
//カメラの取得処理
//==============================================================
Cameracontroller* GetCameracontroller(void)
{
	return &g_cameracontroller;
}