//==============================================================
//
//ACTION_GAME[main.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"block.h"
#include"background.h"
#include"fade.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"gameover.h"
#include"clear.h"
#include"tutorial.h"

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;            //Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;             //現在のモード

//デバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==============================================================
//メイン関数
//==============================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hinstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;

	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),            //WINDCLASSEXのメモリサイズ
		CS_CLASSDC,                    //ウィンドウのスタイル
		WindowProc,                    //ウィンドウプロシージャ
		0,                             //0にする(通常は使用しない)
		0,                             //0にする(通常は使用しない)
		hInstance,                     //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),    //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;                                     //ウィンドウハンドル
	MSG msg;                                       //メッセージを格納する変数
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//画面サイズの構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),//ウィンドウの幅
		(rect.bottom - rect.top),//ウィンドウの高さ
		NULL,
		NULL,
		hInstance,
		NULL);

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能の設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);        //クライアント領域を更新

	DWORD dwFrameCount; //フレームカウント
	DWORD dwFPSLastTime;//最後にFPSを計測した時刻

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg); //ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();//現在時刻を取得

			if (dwCurrentTime - dwExecLastTime >= 1000 / 60)
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;//フレームカウントを加算
			}
		}
	}

	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==============================================================
//ウィンドウプロシージャ
//==============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}

//==============================================================
//初期化処理
//==============================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;       //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ

	//Direct3Dオブジェクト作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));                         //パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                      //ゲーム画面のサイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                    //ゲーム画面のサイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;                     //バックバッファの形式
	d3dpp.BackBufferCount = 1;                                 //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                  //ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;                       //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                 //デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;                                  //ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;  //インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行なう)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//==============================================================
	//各種オブジェクトの初期化処理
	//==============================================================
	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	/*InitBackground();
	InitPlayer();
	InitBlock();

	//床
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 25.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 125.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 175.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 225.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 275.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 325.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 375.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 425.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 525.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 575.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 625.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 675.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 725.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 825.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 875.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 925.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 975.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1025.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1125.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1175.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1225.0f, SCREEN_HEIGHT - 25.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1275.0f, SCREEN_HEIGHT - 25.0f, 0.0f));

	//段差1
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 500.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 450.0f - 50.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 450.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f - 50.0f, SCREEN_HEIGHT - 75.0f, 0.0f));

	//浮いているブロック1 - タイプ変える
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, SCREEN_HEIGHT - 240.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1050.0f, SCREEN_HEIGHT - 240.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1100.0f, SCREEN_HEIGHT - 240.0f, 0.0f));

	//壁 - タイプ変える
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 125.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 225.0f, 0.0f));
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 75.0f, SCREEN_HEIGHT - 175.0f, 0.0f));

	////動作確認用
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 275.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 150.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, SCREEN_HEIGHT - 75.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 175.0f, 0.0f));
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1100.0f, SCREEN_HEIGHT - 300.0f, 0.0f));*/

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void Uninit(void)
{
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UninitTitle();
		break;

	case MODE_GAME://ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT://リザルト画面
		UninitResult();
		break;

	case MODE_GAMEOVER://ゲームオーバー画面
		UninitGameover();
		break;

	case MODE_CLEAR://クリア画面
		UninitClear();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UninitTutorial();
		break;
	}

	//==============================================================
	//各種オブジェクトの終了処理
	//==============================================================
	//UninitBackground();
	//UninitPlayer();
	UninitKeyboard();
	//UninitBlock();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//==============================================================
//更新処理
//==============================================================
void Update(void)
{
	//==============================================================
	//各種オブジェクトの更新処理
	//==============================================================
	//UpdateBackground();
	//UpdatePlayer();
	UpdateKeyboard();
	//UpdateBlock();

	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UpdateTitle();
		break;

	case MODE_GAME://ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT://リザルト画面
		UpdateResult();
		break;

	case MODE_GAMEOVER://ゲームオーバー画面
		UpdateGameover();
		break;

	case MODE_CLEAR://クリア画面
		UpdateClear();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UpdateTutorial();
		break;
	}

	UpdateFade();
}

//==============================================================
//描画処理
//==============================================================
void Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//==============================================================
		//各種オブジェクトの描画処理
		//==============================================================
		//DrawBackground();
		//DrawBlock();
		//DrawPlayer();

		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面
			DrawTitle();
			break;

		case MODE_GAME://ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT://リザルト画面
			DrawResult();
			break;

		case MODE_GAMEOVER://ゲームオーバー画面
			DrawGameover();
			break;

		case MODE_CLEAR://クリア画面
			DrawClear();
			break;

		case MODE_TUTORIAL://チュートリアル画面
			DrawTutorial();
			break;
		}

		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==============================================================
//モードの設定
//==============================================================
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UninitTitle();
		break;

	case MODE_GAME://ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT://リザルト画面
		UninitResult();
		break;

	case MODE_GAMEOVER://ゲームオーバー画面
		UninitGameover();
		break;

	case MODE_CLEAR://クリア画面
		UninitClear();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UninitTutorial();
		break;
	}

	//新しい画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE://タイトル画面
		InitTitle();
		break;

	case MODE_GAME://ゲーム画面
		InitGame();
		break;

	case MODE_RESULT://リザルト画面
		InitResult();
		break;

	case MODE_GAMEOVER://ゲームオーバー画面
		InitGameover();
		break;

	case MODE_CLEAR://クリア画面
		InitClear();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		InitTutorial();
		break;
	}

	g_mode = mode;
}

//==============================================================
//モードの取得
//==============================================================
MODE GetMode(void)
{
	return g_mode;
}