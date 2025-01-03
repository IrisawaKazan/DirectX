//==============================================================
//
//3D_GAME[light.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"light.h"

D3DLIGHT9 g_light[MAX_LIGHT];//ライト情報

//==============================================================
//ライトの初期化処理
//==============================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	D3DXVECTOR3 vecDir;//ライトの方向ベクトル

	//ライトをクリアする
	ZeroMemory(&g_light, sizeof(g_light));

	//=========
	//ライト0
	//=========
	//ライト0の情報を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;

	//ライト0の拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライト0の方向を設定
	vecDir = D3DXVECTOR3(1.5f, -1.5f, -1.5f);

	//正規化する(大きさ位置のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[0].Direction = vecDir;

	//ライト0の設定をする
	pDevice->SetLight(0, &g_light[0]);

	//ライト0を有効にする(ON,OFF)
	pDevice->LightEnable(0, TRUE);

	//=========
	//ライト1
	//=========
	//ライト1の情報を設定
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//ライト1の拡散光を設定
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライト1の方向を設定
	vecDir = D3DXVECTOR3(-1.5f, -1.5f, 1.5f);

	//正規化する(大きさ位置のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[1].Direction = vecDir;

	//ライト1の設定をする
	pDevice->SetLight(1, &g_light[1]);

	//ライト1を有効にする(ON,OFF)
	pDevice->LightEnable(1, TRUE);

	//=========
	//ライト2
	//=========
	//ライト2の情報を設定
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	//ライト2の拡散光を設定
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライト2の方向を設定
	vecDir = D3DXVECTOR3(-1.5f, -1.5f, -1.5f);

	//正規化する(大きさ位置のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[2].Direction = vecDir;

	//ライト2の設定をする
	pDevice->SetLight(2, &g_light[2]);

	//ライト2を有効にする(ON,OFF)
	pDevice->LightEnable(2, TRUE);

	//=========
	//ライト3
	//=========
	//ライト3の情報を設定
	g_light[3].Type = D3DLIGHT_DIRECTIONAL;

	//ライト3の拡散光を設定
	g_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライト3の方向を設定
	vecDir = D3DXVECTOR3(1.5f, -1.5f, 1.5f);

	//正規化する(大きさ位置のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light[3].Direction = vecDir;

	//ライト3の設定をする
	pDevice->SetLight(3, &g_light[3]);

	//ライト3を有効にする(ON,OFF)
	pDevice->LightEnable(3, TRUE);
}

//==============================================================
//ライトの終了処理
//==============================================================
void UninitLight(void)
{

}

//==============================================================
//ライトの更新処理
//==============================================================
void UpdateLight(void)
{

}