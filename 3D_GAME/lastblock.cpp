//==============================================================
//
//[lastblock.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"lastblock.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureLastBlock[MAX_LBLOCK] = {};
LastBlock g_lastblock[MAX_LBLOCK];

//==============================================================
//ラストブロックの初期化処理
//==============================================================
void InitLastBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		g_lastblock[nCntLastBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_lastblock[nCntLastBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].pMesh = NULL;
		g_lastblock[nCntLastBlock].pBuffMat = NULL;
		g_lastblock[nCntLastBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_lastblock[nCntLastBlock].dwNumMat = 0;
		g_lastblock[nCntLastBlock].mtxWorld = {};
		g_lastblock[nCntLastBlock].bUse = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\boxlast100.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_lastblock[nCntLastBlock].pBuffMat,
			NULL,
			&g_lastblock[nCntLastBlock].dwNumMat,
			&g_lastblock[nCntLastBlock].pMesh);

		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファのポインタ

		//頂点数の取得
		nNumVtx = g_lastblock[nCntLastBlock].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_lastblock[nCntLastBlock].pMesh->GetFVF());

		//頂点バッファのロック
		g_lastblock[nCntLastBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値,最大値を取得
			if (vtx.x <= g_lastblock[nCntLastBlock].vtxMin.x)
			{
				g_lastblock[nCntLastBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_lastblock[nCntLastBlock].vtxMin.y)
			{
				g_lastblock[nCntLastBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_lastblock[nCntLastBlock].vtxMin.z)
			{
				g_lastblock[nCntLastBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_lastblock[nCntLastBlock].vtxMax.x)
			{
				g_lastblock[nCntLastBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_lastblock[nCntLastBlock].vtxMax.y)
			{
				g_lastblock[nCntLastBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_lastblock[nCntLastBlock].vtxMax.z)
			{
				g_lastblock[nCntLastBlock].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_lastblock[nCntLastBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルのデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_lastblock[nCntLastBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_lastblock[nCntLastBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//このファイル名を使用してテクスチャを読み込む


				//テクスチャの読み込み


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureLastBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//ラストブロックの終了処理
//==============================================================
void UninitLastBlock(void)
{
	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		//メッシュの破棄
		if (g_lastblock[nCntLastBlock].pMesh != NULL)
		{
			g_lastblock[nCntLastBlock].pMesh->Release();
			g_lastblock[nCntLastBlock].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_lastblock[nCntLastBlock].pBuffMat != NULL)
		{
			g_lastblock[nCntLastBlock].pBuffMat->Release();
			g_lastblock[nCntLastBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//ラストブロックの更新処理
//==============================================================
void UpdateLastBlock(void)
{
	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == true)
		{
			if (g_lastblock[nCntLastBlock].nType == 1)
			{
				//右に動く
				g_lastblock[nCntLastBlock].pos.x += sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.x += cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
			if (g_lastblock[nCntLastBlock].nType == 2)
			{
				//左に動く
				g_lastblock[nCntLastBlock].pos.x -= sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.x -= cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
			if (g_lastblock[nCntLastBlock].nType == 3)
			{
				//奥に動く
				g_lastblock[nCntLastBlock].pos.x += sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.z += cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
			if (g_lastblock[nCntLastBlock].nType == 4)
			{
				//手前に動く
				g_lastblock[nCntLastBlock].pos.x -= sinf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
				g_lastblock[nCntLastBlock].pos.z -= cosf(g_lastblock[nCntLastBlock].rot.y) * MAX_MLBLOCK / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//ラストブロックの描画処理
//==============================================================
void DrawLastBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_lastblock[nCntLastBlock].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_lastblock[nCntLastBlock].rot.y, g_lastblock[nCntLastBlock].rot.x, g_lastblock[nCntLastBlock].rot.z);
			D3DXMatrixMultiply(&g_lastblock[nCntLastBlock].mtxWorld, &g_lastblock[nCntLastBlock].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_lastblock[nCntLastBlock].pos.x, g_lastblock[nCntLastBlock].pos.y, g_lastblock[nCntLastBlock].pos.z);
			D3DXMatrixMultiply(&g_lastblock[nCntLastBlock].mtxWorld, &g_lastblock[nCntLastBlock].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_lastblock[nCntLastBlock].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルのデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_lastblock[nCntLastBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_lastblock[nCntLastBlock].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureLastBlock[nCntMat]);//今はNULL

				//モデル(パーツ)の描画
				g_lastblock[nCntLastBlock].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを元に戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//ラストブロックの設定処理
//==============================================================
void SetLastBlock(D3DXVECTOR3 pos, int type)
{
	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == false)
		{//ブロックの使用されていない
			g_lastblock[nCntLastBlock].pos = pos;
			g_lastblock[nCntLastBlock].nType = type;

			g_lastblock[nCntLastBlock].bUse = true;//使用している状態にする

			break;
		}
	}
}

//==============================================================
//ラストブロックのX軸の当たり判定処理
//==============================================================
void CollisionLastBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntLastBlock = 0; nCntLastBlock < MAX_LBLOCK; nCntLastBlock++)
	{
		if (g_lastblock[nCntLastBlock].bUse == true)
		{
			//左右のめり込み判定
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_lastblock[nCntLastBlock].pos.z + g_lastblock[nCntLastBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_lastblock[nCntLastBlock].pos.z - g_lastblock[nCntLastBlock].vtxMin.z * 2.0f)
			{
				//左から右へ
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_lastblock[nCntLastBlock].pos.x + g_lastblock[nCntLastBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_lastblock[nCntLastBlock].pos.x - g_lastblock[nCntLastBlock].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//仮ゲームオーバー
						pPlayer->bDisp = false;
						//モード設定(ゲームオーバー画面に移行)
						SetFade(MODE_GAMEOVER);
					}
				}
				//右から左へ
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_lastblock[nCntLastBlock].pos.x - g_lastblock[nCntLastBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_lastblock[nCntLastBlock].pos.x + g_lastblock[nCntLastBlock].vtxMax.x)
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
//ハイスピードデッドブロックの取得処理
//==============================================================
LastBlock* GetLastBlock(void) 
{
	return &g_lastblock[MAX_LBLOCK];
}