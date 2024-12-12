//==============================================================
//
//[deadblockhighspeed.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"deadblockhighspeed.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureDeadBlockHS[MAX_DEADHSBLOCK] = {};
DeadBlockHS g_deadblockhs[MAX_DEADHSBLOCK];

//==============================================================
//ハイスピードデッドブロックの初期化処理
//==============================================================
void InitDeadBlockHS(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		g_deadblockhs[nCntDeadBlockHS].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		g_deadblockhs[nCntDeadBlockHS].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].pMesh = NULL;
		g_deadblockhs[nCntDeadBlockHS].pBuffMat = NULL;
		g_deadblockhs[nCntDeadBlockHS].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_deadblockhs[nCntDeadBlockHS].dwNumMat = 0;
		g_deadblockhs[nCntDeadBlockHS].mtxWorld = {};
		g_deadblockhs[nCntDeadBlockHS].bUse = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\boxdeadhighspeed000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_deadblockhs[nCntDeadBlockHS].pBuffMat,
			NULL,
			&g_deadblockhs[nCntDeadBlockHS].dwNumMat,
			&g_deadblockhs[nCntDeadBlockHS].pMesh);

		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファのポインタ

		//頂点数の取得
		nNumVtx = g_deadblockhs[nCntDeadBlockHS].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_deadblockhs[nCntDeadBlockHS].pMesh->GetFVF());

		//頂点バッファのロック
		g_deadblockhs[nCntDeadBlockHS].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値,最大値を取得
			if (vtx.x <= g_deadblockhs[nCntDeadBlockHS].vtxMin.x)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_deadblockhs[nCntDeadBlockHS].vtxMin.y)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_deadblockhs[nCntDeadBlockHS].vtxMin.z)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMin.z = vtx.z;
			}

			if (vtx.x <= g_deadblockhs[nCntDeadBlockHS].vtxMax.x)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMax.x = vtx.x;
			}

			if (vtx.y <= g_deadblockhs[nCntDeadBlockHS].vtxMax.y)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMax.y = vtx.y;
			}

			if (vtx.z <= g_deadblockhs[nCntDeadBlockHS].vtxMax.z)
			{
				g_deadblockhs[nCntDeadBlockHS].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_deadblockhs[nCntDeadBlockHS].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルのデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_deadblockhs[nCntDeadBlockHS].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_deadblockhs[nCntDeadBlockHS].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//このファイル名を使用してテクスチャを読み込む


				//テクスチャの読み込み


				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureDeadBlockHS[nCntMat]);
			}
		}
	}
}

//==============================================================
//ハイスピードデッドブロックの終了処理
//==============================================================
void UninitDeadBlockHS(void)
{
	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		//メッシュの破棄
		if (g_deadblockhs[nCntDeadBlockHS].pMesh != NULL)
		{
			g_deadblockhs[nCntDeadBlockHS].pMesh->Release();
			g_deadblockhs[nCntDeadBlockHS].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_deadblockhs[nCntDeadBlockHS].pBuffMat != NULL)
		{
			g_deadblockhs[nCntDeadBlockHS].pBuffMat->Release();
			g_deadblockhs[nCntDeadBlockHS].pBuffMat = NULL;
		}
	}
}

//==============================================================
//ハイスピードデッドブロックの更新処理
//==============================================================
void UpdateDeadBlockHS(void)
{
	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == true)
		{
			if (g_deadblockhs[nCntDeadBlockHS].nType == 1)
			{
				//右に動く
				g_deadblockhs[nCntDeadBlockHS].pos.x += sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.x += cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
			if (g_deadblockhs[nCntDeadBlockHS].nType == 2)
			{
				//左に動く
				g_deadblockhs[nCntDeadBlockHS].pos.x -= sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.x -= cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
			if (g_deadblockhs[nCntDeadBlockHS].nType == 3)
			{
				//奥に動く
				g_deadblockhs[nCntDeadBlockHS].pos.x += sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.z += cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
			if (g_deadblockhs[nCntDeadBlockHS].nType == 4)
			{
				//手前に動く
				g_deadblockhs[nCntDeadBlockHS].pos.x -= sinf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
				g_deadblockhs[nCntDeadBlockHS].pos.z -= cosf(g_deadblockhs[nCntDeadBlockHS].rot.y) * MAX_MDHSBLOCK / sqrtf(2.0f);
			}
		}
	}
}

//==============================================================
//ハイスピードデッドブロックの描画処理
//==============================================================
void DrawDeadBlockHS(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_deadblockhs[nCntDeadBlockHS].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_deadblockhs[nCntDeadBlockHS].rot.y, g_deadblockhs[nCntDeadBlockHS].rot.x, g_deadblockhs[nCntDeadBlockHS].rot.z);
			D3DXMatrixMultiply(&g_deadblockhs[nCntDeadBlockHS].mtxWorld, &g_deadblockhs[nCntDeadBlockHS].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_deadblockhs[nCntDeadBlockHS].pos.x, g_deadblockhs[nCntDeadBlockHS].pos.y, g_deadblockhs[nCntDeadBlockHS].pos.z);
			D3DXMatrixMultiply(&g_deadblockhs[nCntDeadBlockHS].mtxWorld, &g_deadblockhs[nCntDeadBlockHS].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_deadblockhs[nCntDeadBlockHS].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルのデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_deadblockhs[nCntDeadBlockHS].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_deadblockhs[nCntDeadBlockHS].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureDeadBlockHS[nCntMat]);//今はNULL

				//モデル(パーツ)の描画
				g_deadblockhs[nCntDeadBlockHS].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを元に戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//==============================================================
//ハイスピードデッドブロックの設定処理
//==============================================================
void SetDeadBlockHS(D3DXVECTOR3 pos, int type)
{
	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == false)
		{//ブロックの使用されていない
			g_deadblockhs[nCntDeadBlockHS].pos = pos;
			g_deadblockhs[nCntDeadBlockHS].nType = type;

			g_deadblockhs[nCntDeadBlockHS].bUse = true;//使用している状態にする

			break;
		}
	}
}

//==============================================================
//ハイスピードデッドブロックのX軸の当たり判定処理
//==============================================================
void CollisionDeadBlockHSX(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntDeadBlockHS = 0; nCntDeadBlockHS < MAX_DEADHSBLOCK; nCntDeadBlockHS++)
	{
		if (g_deadblockhs[nCntDeadBlockHS].bUse == true)
		{
			//左右のめり込み判定
			if (pPlayer->pos.z + pPlayer->size.z / 2.0f > g_deadblockhs[nCntDeadBlockHS].pos.z + g_deadblockhs[nCntDeadBlockHS].vtxMax.z &&
				pPlayer->pos.z + pPlayer->size.z / 2.0f < g_deadblockhs[nCntDeadBlockHS].pos.z - g_deadblockhs[nCntDeadBlockHS].vtxMin.z * 2.0f)
			{
				//左から右へ
				if (pPlayer->posOld.x + pPlayer->size.x / 2.0f > g_deadblockhs[nCntDeadBlockHS].pos.x + g_deadblockhs[nCntDeadBlockHS].vtxMin.x &&
					pPlayer->pos.x + pPlayer->size.x / 2.0f < g_deadblockhs[nCntDeadBlockHS].pos.x - g_deadblockhs[nCntDeadBlockHS].vtxMin.x)
				{
					if (GetFade() == FADE_NONE)
					{//仮ゲームオーバー
						pPlayer->bDisp = false;
						//モード設定(ゲームオーバー画面に移行)
						SetFade(MODE_GAMEOVER);
					}
				}
				//右から左へ
				if (pPlayer->posOld.x - pPlayer->size.x / 2.0f < g_deadblockhs[nCntDeadBlockHS].pos.x - g_deadblockhs[nCntDeadBlockHS].vtxMax.x &&
					pPlayer->pos.x - pPlayer->size.x / 2.0f > g_deadblockhs[nCntDeadBlockHS].pos.x + g_deadblockhs[nCntDeadBlockHS].vtxMax.x)
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
DeadBlockHS* GetDeadBlockHS(void)
{
	return &g_deadblockhs[MAX_DEADHSBLOCK];
}