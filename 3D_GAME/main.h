//=============================================================
//
//3D_GAME[main.h]
//Author:Irisawa Kazan
//
//=============================================================
#ifndef _MAIN_H_//このマクロ定義がされてなかったら
#define _MAIN_H_//2重インクルード防止のマクロ定義

#include<windows.h>
#include"d3dx9.h"                   //描写処理に必要
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告対処用マクロ
#include"dinput.h"                  //入力処理に必要
#include"Xinput.h"                  //ジョイパッド処理に必要
#include"xaudio2.h"                 //サウンド処理に必要

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")   //描写処理に必要
#pragma comment(lib,"d3dx9.lib")  //[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib") //Directコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")//入力処理に必要
#pragma comment(lib,"xinput.lib") //ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME "WindowClass"                                           //ウィンドウクラスの名前
#define WINDOW_NAME "To-RyaNSe ~Both going & returning are Yoi! Yoi! Yoi!~"//ウィンドウの名前
#define SCREEN_WIDTH (1280)                                                //ウィンドウの幅
#define SCREEN_HEIGHT (720)                                                //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;      //座標変換用係数(1.0fで固定)
	D3DCOLOR col;   //座標カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,//タイトル画面
	MODE_GAME,     //ゲーム画面
	MODE_RESULT,   //リザルト画面
	MODE_CLEAR,    //クリア画面
	MODE_GAMEOVER, //ゲームオーバー画面
	MODE_PAUSE,    //ポーズ画面
	MODE_TUTORIAL, //チュートリアル画面
	MODE_MAX
}MODE;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawFPS(void);

#endif