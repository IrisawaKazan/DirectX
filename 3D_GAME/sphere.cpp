//==============================================================
//
//3D_GAME[sphere.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"sphere.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureSphere[1] = {};
Sphere g_sphere;

//==============================================================
//モデルの初期化処理
//==============================================================
void InitSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	g_sphere.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sphere.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sphere.pMesh = NULL;
	g_sphere.pBuffMat = NULL;
	g_sphere.dwNumMat = 0;
	g_sphere.mtxWorld = {};

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\sphere.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_sphere.pBuffMat,
		NULL,
		&g_sphere.dwNumMat,
		&g_sphere.pMesh);

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_sphere.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_sphere.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//このファイル名を使用してテクスチャを読み込む


			//テクスチャの読み込み


			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureSphere[nCntMat]);
		}
	}
}

//==============================================================
//モデルの終了処理
//==============================================================
void UninitSphere(void)
{
	//メッシュの破棄
	if (g_sphere.pMesh != NULL)
	{
		g_sphere.pMesh->Release();
		g_sphere.pMesh = NULL;
	}

	//マテリアルの破棄
	if (g_sphere.pBuffMat != NULL)
	{
		g_sphere.pBuffMat->Release();
		g_sphere.pBuffMat = NULL;
	}
}

//==============================================================
//モデルの更新処理
//==============================================================
void UpdateSphere(void)
{

}

//==============================================================
//モデルの描画処理
//==============================================================
void DrawSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_sphere.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_sphere.rot.y, g_sphere.rot.x, g_sphere.rot.z);
	D3DXMatrixMultiply(&g_sphere.mtxWorld, &g_sphere.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_sphere.pos.x, g_sphere.pos.y, g_sphere.pos.z);
	D3DXMatrixMultiply(&g_sphere.mtxWorld, &g_sphere.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_sphere.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_sphere.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_sphere.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureSphere[nCntMat]);//今はNULL

		//モデル(パーツ)の描画
		g_sphere.pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}