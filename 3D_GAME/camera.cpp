//==============================================================
//
//3D_GAME[camera.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"camera.h"

//グローバル変数
Camera g_camera;//カメラ情報

//==============================================================
//カメラの初期化処理
//==============================================================
void InitCamera(void)
{
	Player* pPlayer = GetPlayer();

	//視点,注視点,上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -250.0f);//どっちか
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_camera.posR = pPlayer->pos;
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x) +
		(g_camera.posR.y - g_camera.posV.y) * (g_camera.posR.y - g_camera.posV.y) +
		(g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z));
}

//==============================================================
//カメラの終了処理
//==============================================================
void UninitCamera(void)
{

}

//==============================================================
//カメラの更新処理
//==============================================================
void UpdateCamera(void)
{
	Player* pPlayer = GetPlayer();

	//カメラの追従
	g_camera.posRDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posRDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	g_camera.posV.x = pPlayer->pos.x;

	g_camera.posR.x += (pPlayer->pos.x - g_camera.posR.x) * 0.1f;
	g_camera.posR.z += (pPlayer->pos.z - g_camera.posR.z) * 0.1f;

	////注視点の旋回
	//if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_camera.rot.y -= 0.02f;

	//	//角度の正規化
	//	if (-D3DX_PI > g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
	//	}

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
	//else if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_camera.rot.y += 0.02f;
	//
	//	//角度の正規化
	//	if (D3DX_PI < g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
	//	}
	//
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}

	////視点の旋回
	//if (GetKeyboardPress(DIK_Z) == true)
	//{
	//	g_camera.rot.y -= 0.02f;

	//	//角度の正規化
	//	if (-D3DX_PI > g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
	//	}

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
	//else if (GetKeyboardPress(DIK_C) == true)
	//{
	//	g_camera.rot.y += 0.02f;
	//
	//	//角度の正規化
	//	if (D3DX_PI < g_camera.rot.y)
	//	{
	//		g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
	//	}
	//
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	//}

	////カメラの移動
	//if (GetKeyboardPress(DIK_LEFT) == true)
	//{//左
	//	if (GetKeyboardPress(DIK_UP) == true)
	//	{//左上に移動
	//		//左
	//		g_camera.posV.x -= cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//上
	//		g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN) == true)
	//	{//左下に移動
	//		//左
	//		g_camera.posV.x -= cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//下
	//		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else
	//	{//左に移動
	//		g_camera.posV.x -= cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_RIGHT) == true)
	//{//右
	//	if (GetKeyboardPress(DIK_UP) == true)
	//	{//右上に移動
	//		//右
	//		g_camera.posV.x += cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//上
	//		g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN) == true)
	//	{//右下に移動
	//		//右
	//		g_camera.posV.x += cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

	//		//下
	//		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//	else
	//	{//右に移動
	//		g_camera.posV.x += cosf(g_camera.rot.y) * 1.0f;
	//		g_camera.posV.z -= sinf(g_camera.rot.y) * 1.0f;

	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_UP) == true)
	//{//上
	//	g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
	//	g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
	//else if (GetKeyboardPress(DIK_DOWN) == true)
	//{//下
	//	g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
	//	g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	//}
}

//==============================================================
//カメラの設定処理
//==============================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//==============================================================
//カメラの取得処理
//==============================================================
Camera* GetCamera(void)
{
	return &g_camera;
}