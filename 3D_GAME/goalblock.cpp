//==============================================================
//
//3D_GAME[goalblock.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"goalblock.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureGoalBlock[MAX_GBLOCK] = {};
GoalBlock g_goalblock[MAX_GBLOCK];

//==============================================================
//ゴールブロックの初期化処理
//==============================================================
void InitGoalBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		g_goalblock[nCntGoalBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_goalblock[nCntGoalBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].pMesh = NULL;
		g_goalblock[nCntGoalBlock].pBuffMat = NULL;
		g_goalblock[nCntGoalBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_goalblock[nCntGoalBlock].dwNumMat = 0;
		g_goalblock[nCntGoalBlock].mtxWorld = {};
		g_goalblock[nCntGoalBlock].bUse = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\boxgoal000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_goalblock[nCntGoalBlock].pBuffMat,
			NULL,
			&g_goalblock[nCntGoalBlock].dwNumMat,
			&g_goalblock[nCntGoalBlock].pMesh);

		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファのポインタ

		//頂点数の取得
		nNumVtx = g_goalblock[nCntGoalBlock].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_goalblock[nCntGoalBlock].pMesh->GetFVF());

		//頂点バッファのロック
		g_goalblock[nCntGoalBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値,最大値を取得
			if (vtx.x <= g_goalblock[nCntGoalBlock].vtxMin.x)
			{
				g_goalblock[nCntGoalBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_goalblock[nCntGoalBlock].vtxMin.y)
			{
				g_goalblock[nCntGoalBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_goalblock[nCntGoalBlock].vtxMin.z)
			{
				g_goalblock[nCntGoalBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_goalblock[nCntGoalBlock].vtxMax.x)
			{
				g_goalblock[nCntGoalBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_goalblock[nCntGoalBlock].vtxMax.y)
			{
				g_goalblock[nCntGoalBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_goalblock[nCntGoalBlock].vtxMax.z)
			{
				g_goalblock[nCntGoalBlock].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_goalblock[nCntGoalBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルのデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_goalblock[nCntGoalBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_goalblock[nCntGoalBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//このファイル名を使用してテクスチャを読み込む


				//テクスチャの読み込み


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureGoalBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//ゴールブロックの終了処理
//==============================================================
void UninitGoalBlock(void)
{
	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		//メッシュの破棄
		if (g_goalblock[nCntGoalBlock].pMesh != NULL)
		{
			g_goalblock[nCntGoalBlock].pMesh->Release();
			g_goalblock[nCntGoalBlock].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_goalblock[nCntGoalBlock].pBuffMat != NULL)
		{
			g_goalblock[nCntGoalBlock].pBuffMat->Release();
			g_goalblock[nCntGoalBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//ゴールブロックの更新処理
//==============================================================
void UpdateGoalBlock(void)
{
	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			if (g_goalblock[nCntGoalBlock].nType == 1)
			{
				//奥に動く
				g_goalblock[nCntGoalBlock].pos.x += sinf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS1 / sqrtf(2.0f);
				g_goalblock[nCntGoalBlock].pos.z += cosf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS1 / sqrtf(2.0f);
			}
		}
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			if (g_goalblock[nCntGoalBlock].nType == 2)
			{
				//奥に動く
				g_goalblock[nCntGoalBlock].pos.x += sinf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS2 / sqrtf(2.0f);
				g_goalblock[nCntGoalBlock].pos.z += cosf(g_goalblock[nCntGoalBlock].rot.y) * MAX_MGBLOCKS2 / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//ゴールブロックの描画処理
//==============================================================
void DrawGoalBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_goalblock[nCntGoalBlock].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goalblock[nCntGoalBlock].rot.y, g_goalblock[nCntGoalBlock].rot.x, g_goalblock[nCntGoalBlock].rot.z);
			D3DXMatrixMultiply(&g_goalblock[nCntGoalBlock].mtxWorld, &g_goalblock[nCntGoalBlock].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_goalblock[nCntGoalBlock].pos.x, g_goalblock[nCntGoalBlock].pos.y, g_goalblock[nCntGoalBlock].pos.z);
			D3DXMatrixMultiply(&g_goalblock[nCntGoalBlock].mtxWorld, &g_goalblock[nCntGoalBlock].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_goalblock[nCntGoalBlock].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルのデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_goalblock[nCntGoalBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_goalblock[nCntGoalBlock].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureGoalBlock[nCntMat]);//今はNULL

				//モデル(パーツ)の描画
				g_goalblock[nCntGoalBlock].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを元に戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//ゴールブロックの設定処理
//==============================================================
void SetGoalBlock(D3DXVECTOR3 pos, int type)
{
	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == false)
		{//ブロックの使用されていない
			g_goalblock[nCntGoalBlock].pos = pos;
			g_goalblock[nCntGoalBlock].nType = type;

			g_goalblock[nCntGoalBlock].bUse = true;//使用している状態にする

			break;
		}
	}
}

//==============================================================
//ゴールブロックのX軸の当たり判定処理
//==============================================================
void CollisionGoalBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntGoalBlock = 0; nCntGoalBlock < MAX_GBLOCK; nCntGoalBlock++)
	{
		if (g_goalblock[nCntGoalBlock].bUse == true)
		{
			//左右のめり込み判定
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_goalblock[nCntGoalBlock].pos.z + g_goalblock[nCntGoalBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_goalblock[nCntGoalBlock].pos.z - g_goalblock[nCntGoalBlock].vtxMin.z * 2.0f)
			{
				//左から右へ
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_goalblock[nCntGoalBlock].pos.x + g_goalblock[nCntGoalBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_goalblock[nCntGoalBlock].pos.x - g_goalblock[nCntGoalBlock].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//ゲームオーバー
						pPlayer->bDisp = false;
						//モード設定(ゲームオーバー画面に移行)
						SetFade(MODE_GAMEOVER);
					}
				}
				//右から左へ
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_goalblock[nCntGoalBlock].pos.x - g_goalblock[nCntGoalBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_goalblock[nCntGoalBlock].pos.x + g_goalblock[nCntGoalBlock].vtxMax.x)
				{
					if (GetFade() == FADE_NONE)
					{//ゲームオーバー
						pPlayer->bDisp = false;
						//モード設定(ゲームオーバー画面に移行)
						SetFade(MODE_GAMEOVER);
					}
				}
			}
		}
	}
}

//==============================================================
//ゴールブロックの取得処理
//==============================================================
GoalBlock* GetGoalBlock(void) 
{
	return &g_goalblock[MAX_GBLOCK];
}