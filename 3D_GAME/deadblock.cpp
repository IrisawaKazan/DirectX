//==============================================================
//
//[deadblock.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"deadblock.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureDeadBlock[MAX_DEADBLOCK] = {};
DeadBlock g_deadblock[MAX_DEADBLOCK];

//==============================================================
//デッドブロックの初期化処理
//==============================================================
void InitDeadBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		g_deadblock[nCntDeadBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_deadblock[nCntDeadBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].pMesh = NULL;
		g_deadblock[nCntDeadBlock].pBuffMat = NULL;
		g_deadblock[nCntDeadBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblock[nCntDeadBlock].dwNumMat = 0;
		g_deadblock[nCntDeadBlock].mtxWorld = {};
		g_deadblock[nCntDeadBlock].bUse = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\boxdead000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_deadblock[nCntDeadBlock].pBuffMat,
			NULL,
			&g_deadblock[nCntDeadBlock].dwNumMat,
			&g_deadblock[nCntDeadBlock].pMesh);

		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファのポインタ

		//頂点数の取得
		nNumVtx = g_deadblock[nCntDeadBlock].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_deadblock[nCntDeadBlock].pMesh->GetFVF());

		//頂点バッファのロック
		g_deadblock[nCntDeadBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値,最大値を取得
			if (vtx.x <= g_deadblock[nCntDeadBlock].vtxMin.x)
			{
				g_deadblock[nCntDeadBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_deadblock[nCntDeadBlock].vtxMin.y)
			{
				g_deadblock[nCntDeadBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_deadblock[nCntDeadBlock].vtxMin.z)
			{
				g_deadblock[nCntDeadBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_deadblock[nCntDeadBlock].vtxMax.x)
			{
				g_deadblock[nCntDeadBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_deadblock[nCntDeadBlock].vtxMax.y)
			{
				g_deadblock[nCntDeadBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_deadblock[nCntDeadBlock].vtxMax.z)
			{
				g_deadblock[nCntDeadBlock].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_deadblock[nCntDeadBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルのデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_deadblock[nCntDeadBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_deadblock[nCntDeadBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//このファイル名を使用してテクスチャを読み込む


				//テクスチャの読み込み


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureDeadBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//デッドブロックの終了処理
//==============================================================
void UninitDeadBlock(void)
{
	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		//メッシュの破棄
		if (g_deadblock[nCntDeadBlock].pMesh != NULL)
		{
			g_deadblock[nCntDeadBlock].pMesh->Release();
			g_deadblock[nCntDeadBlock].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_deadblock[nCntDeadBlock].pBuffMat != NULL)
		{
			g_deadblock[nCntDeadBlock].pBuffMat->Release();
			g_deadblock[nCntDeadBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//デッドブロックの更新処理
//==============================================================
void UpdateDeadBlock(void)
{
	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == true)
		{
			if (g_deadblock[nCntDeadBlock].nType == 1)
			{
				//右に動く
				g_deadblock[nCntDeadBlock].pos.x += sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.x += cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
			if (g_deadblock[nCntDeadBlock].nType == 2)
			{
				//左に動く
				g_deadblock[nCntDeadBlock].pos.x -= sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.x -= cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
			if (g_deadblock[nCntDeadBlock].nType == 3)
			{
				//奥に動く
				g_deadblock[nCntDeadBlock].pos.x += sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.z += cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
			if (g_deadblock[nCntDeadBlock].nType == 4)
			{
				//手前に動く
				g_deadblock[nCntDeadBlock].pos.x -= sinf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
				g_deadblock[nCntDeadBlock].pos.z -= cosf(g_deadblock[nCntDeadBlock].rot.y) * MAX_MDBLOCK / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//デッドブロックの描画処理
//==============================================================
void DrawDeadBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_deadblock[nCntDeadBlock].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_deadblock[nCntDeadBlock].rot.y, g_deadblock[nCntDeadBlock].rot.x, g_deadblock[nCntDeadBlock].rot.z);
			D3DXMatrixMultiply(&g_deadblock[nCntDeadBlock].mtxWorld, &g_deadblock[nCntDeadBlock].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_deadblock[nCntDeadBlock].pos.x, g_deadblock[nCntDeadBlock].pos.y, g_deadblock[nCntDeadBlock].pos.z);
			D3DXMatrixMultiply(&g_deadblock[nCntDeadBlock].mtxWorld, &g_deadblock[nCntDeadBlock].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_deadblock[nCntDeadBlock].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルのデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_deadblock[nCntDeadBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_deadblock[nCntDeadBlock].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureDeadBlock[nCntMat]);//今はNULL

				//モデル(パーツ)の描画
				g_deadblock[nCntDeadBlock].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを元に戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//デッドブロックの設定処理
//==============================================================
void SetDeadBlock(D3DXVECTOR3 pos, int type)
{
	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == false)
		{//ブロックの使用されていない
			g_deadblock[nCntDeadBlock].pos = pos;
			g_deadblock[nCntDeadBlock].nType = type;

			g_deadblock[nCntDeadBlock].bUse = true;//使用している状態にする

			break;
		}
	}
}

//==============================================================
//デッドブロックのX軸の当たり判定処理
//==============================================================
void CollisionDeadBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntDeadBlock = 0; nCntDeadBlock < MAX_DEADBLOCK; nCntDeadBlock++)
	{
		if (g_deadblock[nCntDeadBlock].bUse == true)
		{
			//左右のめり込み判定
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_deadblock[nCntDeadBlock].pos.z + g_deadblock[nCntDeadBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_deadblock[nCntDeadBlock].pos.z - g_deadblock[nCntDeadBlock].vtxMin.z * 2.0f)
			{
				//左から右へ
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_deadblock[nCntDeadBlock].pos.x + g_deadblock[nCntDeadBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_deadblock[nCntDeadBlock].pos.x - g_deadblock[nCntDeadBlock].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//仮ゲームオーバー
						pPlayer->bDisp = false;
						//モード設定(ゲームオーバー画面に移行)
						SetFade(MODE_GAMEOVER);
					}
				}
				//右から左へ
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_deadblock[nCntDeadBlock].pos.x - g_deadblock[nCntDeadBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_deadblock[nCntDeadBlock].pos.x + g_deadblock[nCntDeadBlock].vtxMax.x)
				{
					if (GetFade() == FADE_NONE)
					{//仮ゲームオーバー
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
//デッドブロックの取得処理
//==============================================================
DeadBlock* GetDeadBlock(void)
{
	return &g_deadblock[MAX_DEADBLOCK];
}