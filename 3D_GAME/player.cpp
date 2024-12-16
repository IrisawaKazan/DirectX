//==============================================================
//
//3D_GAME[player.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"player.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_PTEXTURE] = {};
Player g_player;

//==============================================================
//プレイヤーの初期化処理
//==============================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, -140.0f);
	//g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.pMesh = NULL;
	//g_player.pBuffMat = NULL;
	//g_player.dwNumMat = 0;
	//g_player.mtxWorld = {};
	//g_player.aModel->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.aModel->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\00_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].dwNumMat,
		&g_player.aModel[0].pMesh);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\01_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,
		NULL,
		&g_player.aModel[1].dwNumMat,
		&g_player.aModel[1].pMesh);

	//パーツの総数
	g_player.nNumModel = MAX_PARTS;

	//各パーツ数の階層構造設定
	g_player.aModel[0].nIdxModelParant = -1;               //親モデルのインデックスの設定
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置の初期化設定
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期化設定

	g_player.aModel[1].nIdxModelParant = 0;                 //親モデルのインデックスの設定
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 17.5f, 0.0f);//位置の初期化設定
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化設定

	int nNumVtx;   //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファのポインタ

	//頂点数の取得
	nNumVtx = g_player.aModel[0].pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].pMesh->GetFVF());

	//頂点バッファのロック
	g_player.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//頂点座標を比較してモデルの最小値,最大値を取得
		if (vtx.x <= g_player.vtxMin.x)
		{
			g_player.vtxMin.x = vtx.x;
		}

		if (vtx.y <= g_player.vtxMin.y)
		{
			g_player.vtxMin.y = vtx.y;
		}

		if (vtx.z <= g_player.vtxMin.z)
		{
			g_player.vtxMin.z = vtx.z;
		}

		if (vtx.x >= g_player.vtxMax.x)
		{
			g_player.vtxMax.x = vtx.x;
		}

		if (vtx.y >= g_player.vtxMax.y)
		{
			g_player.vtxMax.y = vtx.y;
		}

		if (vtx.z >= g_player.vtxMax.z)
		{
			g_player.vtxMax.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	g_player.size = D3DXVECTOR3(g_player.vtxMax.x - g_player.vtxMin.x, g_player.vtxMax.y - g_player.vtxMin.y, g_player.vtxMax.z - g_player.vtxMin.z);

	g_player.bDisp = true;

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_player.aModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_player.aModel->dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//このファイル名を使用してテクスチャを読み込む


			//テクスチャの読み込み


			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTexturePlayer[nCntMat]);
		}
	}

	g_player.nIdxShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//==============================================================
//プレイヤーの終了処理
//==============================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		//メッシュの破棄
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//==============================================================
//プレイヤーの更新処理
//==============================================================
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();

	//ブロックとの当たり判定
	{
		CollisionBlockX();
		CollisionBlockZ();
		CollisionDeadBlockX();
		CollisionDeadBlockHSX();
		CollisionGoalBlockX();
		CollisionLastBlockX();
	}

	//前回の位置を保存
	g_player.posOld = g_player.pos;

	//プレイヤー移動
	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//左
			if (GetKeyboardPress(DIK_W) == true)
			{//左奥に移動
				//左
				g_player.pos.x -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//奥
				g_player.pos.x += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//左手前に移動
				//左
				g_player.pos.x -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//手前
				g_player.pos.x -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else
			{//左に移動
				g_player.pos.x -= cosf(pCamera->rot.y) * MAX_PMOVE;
				g_player.pos.z += sinf(pCamera->rot.y) * MAX_PMOVE;
				g_player.rot.y = g_player.rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//右
			if (GetKeyboardPress(DIK_W) == true)
			{//右に移動
				//右
				g_player.pos.x += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//奥
				g_player.pos.x += sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//右手前に移動
				//右
				g_player.pos.x += cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;

				//手前
				g_player.pos.x -= sinf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.pos.z -= cosf(pCamera->rot.y) * MAX_PMOVE / sqrtf(2.0f);
				g_player.rot.y = g_player.rot.y;
			}
			else
			{//右に移動
				g_player.pos.x += cosf(pCamera->rot.y) * MAX_PMOVE;
				g_player.pos.z -= sinf(pCamera->rot.y) * MAX_PMOVE;
				g_player.rot.y = g_player.rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//奥
			g_player.pos.x += sinf(pCamera->rot.y) * MAX_PMOVE;
			g_player.pos.z += cosf(pCamera->rot.y) * MAX_PMOVE;
			g_player.rot.y = g_player.rot.y;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//手前
			g_player.pos.x -= sinf(pCamera->rot.y) * MAX_PMOVE;
			g_player.pos.z -= cosf(pCamera->rot.y) * MAX_PMOVE;
			g_player.rot.y = g_player.rot.y;
		}
	}

	//全モデル(パーツ)の更新
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		//キー情報から位置,向きを算出


		//パーツの位置,向きを設定
		g_player.aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f + nCntModel * 17.5f, 0.0f);
		g_player.aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_player.nCounterMotion++;

	SetPositionShadow(g_player.nIdxShadow, g_player.pos);
}

//==============================================================
//プレイヤーの描画処理
//==============================================================
void DrawPlayer(void)
{
	if (g_player.bDisp == true)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

		pDevice = GetDevice();

		//計算用のマトリックス
		D3DXMATRIX mtxRot, mtxTrans;

		D3DMATERIAL9 matDef;//現在のマテリアル保存用

		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.x, g_player.rot.y, g_player.rot.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//全パーツの描画
		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス
			D3DXMATRIX mtxParent;                 //親のマトリックス

			//パーツのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスを設定
			if (g_player.aModel[nCntModel].nIdxModelParant != -1)
			{//親モデルがある場合
				mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParant].mtxWorld;
			}
			else
			{//親モデルがない場合
				mtxParent = g_player.mtxWorld;
			}

			//マテリアルのデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			//算出したパーツのワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
				&g_player.aModel[nCntModel].mtxWorld,
				&mtxParent);

			//パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&g_player.aModel[nCntModel].mtxWorld);

			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);//今はNULL

				//モデル(パーツ)の描画
				g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを元に戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==============================================================
//プレイヤーの取得処理
//==============================================================
Player* GetPlayer(void)
{
	return &g_player;
}