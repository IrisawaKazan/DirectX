//==============================================================
//
//[block.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"block.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBlock[MAX_BLOCK] = {};
Block g_block[MAX_BLOCK];

//==============================================================
//ブロックの初期化処理
//==============================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_block[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_block[nCntBlock].pMesh = NULL;
		g_block[nCntBlock].pBuffMat = NULL;
		g_block[nCntBlock].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_block[nCntBlock].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_block[nCntBlock].dwNumMat = 0;
		g_block[nCntBlock].mtxWorld = {};
		g_block[nCntBlock].bUse = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\box100.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_block[nCntBlock].pBuffMat,
			NULL,
			&g_block[nCntBlock].dwNumMat,
			&g_block[nCntBlock].pMesh);

		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファのポインタ

		//頂点数の取得
		nNumVtx = g_block[nCntBlock].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_block[nCntBlock].pMesh->GetFVF());

		//頂点バッファのロック
		g_block[nCntBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値,最大値を取得
			if (vtx.x <= g_block[nCntBlock].vtxMin.x)
			{
				g_block[nCntBlock].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_block[nCntBlock].vtxMin.y)
			{
				g_block[nCntBlock].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_block[nCntBlock].vtxMin.z)
			{
				g_block[nCntBlock].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_block[nCntBlock].vtxMax.x)
			{
				g_block[nCntBlock].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_block[nCntBlock].vtxMax.y)
			{
				g_block[nCntBlock].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_block[nCntBlock].vtxMax.z)
			{
				g_block[nCntBlock].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_block[nCntBlock].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルのデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_block[nCntBlock].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_block[nCntBlock].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//このファイル名を使用してテクスチャを読み込む


				//テクスチャの読み込み


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureBlock[nCntMat]);
			}
		}
	}
}

//==============================================================
//ブロックの終了処理
//==============================================================
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//メッシュの破棄
		if (g_block[nCntBlock].pMesh != NULL)
		{
			g_block[nCntBlock].pMesh->Release();
			g_block[nCntBlock].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_block[nCntBlock].pBuffMat != NULL)
		{
			g_block[nCntBlock].pBuffMat->Release();
			g_block[nCntBlock].pBuffMat = NULL;
		}
	}
}

//==============================================================
//ブロックの更新処理
//==============================================================
void UpdateBlock(void)
{

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			////手前に動く(Deadblock用)
			//g_block[nCntBlock].pos.x -= sinf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			//g_block[nCntBlock].pos.z -= cosf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			
			////右に動く
			//g_block[nCntBlock].pos.x += sinf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			//g_block[nCntBlock].pos.x += cosf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);

			////左に動く
			//g_block[nCntBlock].pos.x -= sinf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
			//g_block[nCntBlock].pos.x -= cosf(g_block[nCntBlock].rot.y) * MAX_MBLOCK/*MAX_BLOCKMOVE(MAX_DBLOCKMOVE or MAX_HSBLOCKMOVE or MAX_HSDBLOCKMOVE or MAX_GOALBLOCK)*/ / sqrtf(2.0f);
		}
	}
}

//==============================================================
//ブロックの描画処理
//==============================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_block[nCntBlock].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_block[nCntBlock].rot.y, g_block[nCntBlock].rot.x, g_block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_block[nCntBlock].mtxWorld, &g_block[nCntBlock].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_block[nCntBlock].mtxWorld, &g_block[nCntBlock].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_block[nCntBlock].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルのデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_block[nCntBlock].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_block[nCntBlock].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);//今はNULL

				//モデル(パーツ)の描画
				g_block[nCntBlock].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを元に戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//ブロックの設定処理
//==============================================================
void SetBlock(D3DXVECTOR3 pos)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == false)
		{//ブロックの使用されていない
			g_block[nCntBlock].pos = pos;

			g_block[nCntBlock].bUse = true;//使用している状態にする

			break;
		}
	}
}

//==============================================================
//ブロックのX軸の当たり判定処理
//==============================================================
void CollisionBlockX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			//左右のめり込み判定
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_block[nCntBlock].pos.z + g_block[nCntBlock].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_block[nCntBlock].pos.z - g_block[nCntBlock].vtxMin.z * 2.0f)
			{
				//左から右へ
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_block[nCntBlock].pos.x + g_block[nCntBlock].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_block[nCntBlock].pos.x - g_block[nCntBlock].vtxMin.x)
				{
					//pPlayer->pPosをモデルの左側にくっつける
					pPlayer->pos.x = pPlayer->pos.x / 2.0f + g_block[nCntBlock].pos.x / 2.0f - pPlayer->size.x + g_block[nCntBlock].pos.x / 2.0f + g_block[nCntBlock].vtxMin.x / 2.0f - pPlayer->posOld.x / 2.0f;
					pPlayer->move.x = 0.0f;
				}
				//右から左へ
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_block[nCntBlock].pos.x - g_block[nCntBlock].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_block[nCntBlock].pos.x + g_block[nCntBlock].vtxMax.x)
				{
					//pPlayer->pPosをモデルの右側にくっつける
					pPlayer->pos.x = g_block[nCntBlock].pos.x / 2.0f - g_block[nCntBlock].pos.x / 2.0f - pPlayer->size.x / 2.0f - g_block[nCntBlock].vtxMin.x / 2.0f + pPlayer->posOld.x;
					pPlayer->move.x = 0.0f;
				}
			}
		}
	}
}

//==============================================================
//ブロックのZ軸の当たり判定処理
//==============================================================
void CollisionBlockZ(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_block[nCntBlock].bUse == true)
		{
			////奥行のめり込み判定
			//if (pPlayer->pos.x + pPlayer->size.x / 2.0f > g_block[nCntBlock].pos.x + g_block[nCntBlock].vtxMax.x &&
			//	pPlayer->pos.x + pPlayer->size.x / 2.0f < g_block[nCntBlock].pos.x - g_block[nCntBlock].vtxMin.x * 2.0f)
			//{
			//	//奥から手前へ


			//	//手前から奥へ

			//}
		}
	}
}