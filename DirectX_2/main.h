//==============================================================
//
//SHOOTING GAME[main.h]
//Author:Irisawa Kazan
//
//==============================================================
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
#define CLASS_NAME "WindowClass"//ウィンドウクラスの名前
#define WINDOW_NAME "SHOOTING"  //ウィンドウの名前
#define SCREEN_WIDTH (1280)     //ウィンドウの幅
#define SCREEN_HEIGHT (720)     //ウィンドウの高さ
/*#define ID_BUTTON_FINISH (101)  //終了ボタンのID
#define ID_BUTTON_COPY (102)    //コピーボタンのID
#define ID_EDIT_INPUT (111)     //入力ウィンドウのID
#define ID_EDIT_OUTPUT (121)    //出力ウィンドウのID
#define ID_TIMER (131)          //タイマーのID
#define TIMER_INTERVAL (1000/60)//タイマー発生間隔(ミリ秒)*/
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;      //座標変換用係数(1.0fで固定)
	D3DCOLOR col;   //座標カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,//タイトル画面
	MODE_GAME,     //ゲーム画面
	MODE_RESULT,   //リザルト画面
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