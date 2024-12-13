//==============================================================
//
//3D_GAME[main.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"input.h"
#include"fade.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"gameover.h"
#include"clear.h"
#include"tutorial.h"

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;            //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;             //���݂̃��[�h
LPD3DXFONT g_pFont = NULL;            //�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;                  //FPS�J�E���^

//�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==============================================================
//���C���֐�
//==============================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hinstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;

	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),            //WINDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                    //�E�B���h�E�̃X�^�C��
		WindowProc,                    //�E�B���h�E�v���V�[�W��
		0,                             //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,                             //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,                     //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),    //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;                                     //�E�B���h�E�n���h��
	MSG msg;                                       //���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//��ʃT�C�Y�̍\����

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),//�E�B���h�E�̕�
		(rect.bottom - rect.top),//�E�B���h�E�̍���
		NULL,
		NULL,
		hInstance,
		NULL);

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//����\�̐ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);        //�N���C�A���g�̈���X�V

	DWORD dwFrameCount; //�t���[���J�E���g
	DWORD dwFPSLastTime;//�Ō��FPS���v����������

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();//���ݎ������擾

			if (dwCurrentTime - dwFPSLastTime >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;             //�t���[���J�E���g���N���A
			}

			if (dwCurrentTime - dwExecLastTime >= 1000 / 60)
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;//�t���[���J�E���g�����Z
			}
		}
	}

	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==============================================================
//�E�B���h�E�v���V�[�W��
//==============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}

//==============================================================
//����������
//==============================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;       //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));                         //�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                      //�Q�[����ʂ̃T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                    //�Q�[����ʂ̃T�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;                     //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                 //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                  //�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;                       //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                 //�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;                                  //�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;  //�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs�Ȃ�)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//==============================================================
	//�e��I�u�W�F�N�g�̏���������
	//==============================================================
	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void Uninit(void)
{
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UninitTitle();
		break;

	case MODE_GAME://�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT://���U���g���
		UninitResult();
		break;

	case MODE_GAMEOVER://�Q�[���I�[�o�[���
		UninitGameover();
		break;

	case MODE_CLEAR://�N���A���
		UninitClear();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		UninitTutorial();
		break;
	}

	//==============================================================
	//�e��I�u�W�F�N�g�̏I������
	//==============================================================
	UninitKeyboard();

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//==============================================================
//�X�V����
//==============================================================
void Update(void)
{
	//==============================================================
	//�e��I�u�W�F�N�g�̍X�V����
	//==============================================================
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UpdateTitle();
		break;

	case MODE_GAME://�Q�[�����
		UpdateGame();
		break;

	case MODE_RESULT://���U���g���
		UpdateResult();
		break;

	case MODE_GAMEOVER://�Q�[���I�[�o�[���
		UpdateGameover();
		break;

	case MODE_CLEAR://�N���A���
		UpdateClear();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		UpdateTutorial();
		break;
	}

	UpdateFade();
}

//==============================================================
//�`�揈��
//==============================================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//==============================================================
		//�e��I�u�W�F�N�g�̕`�揈��
		//==============================================================

		switch (g_mode)
		{
		case MODE_TITLE://�^�C�g�����
			DrawTitle();
			break;

		case MODE_GAME://�Q�[�����
			DrawGame();
			break;

		case MODE_RESULT://���U���g���
			DrawResult();
			break;

		case MODE_GAMEOVER://�Q�[���I�[�o�[���
			DrawGameover();
			break;

		case MODE_CLEAR://�N���A���
			DrawClear();
			break;

		case MODE_TUTORIAL://�`���[�g���A�����
			DrawTutorial();
			break;
		}

		DrawFade();

#ifdef _DEBUG

		//FPS�̕\��
		DrawFPS();

#endif

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==============================================================
//���[�h�̐ݒ�
//==============================================================
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UninitTitle();
		break;

	case MODE_GAME://�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT://���U���g���
		UninitResult();
		break;

	case MODE_GAMEOVER://�Q�[���I�[�o�[���
		UninitGameover();
		break;

	case MODE_CLEAR://�N���A���
		UninitClear();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		UninitTutorial();
		break;
	}

	//�V�������(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE://�^�C�g�����
		InitTitle();
		break;

	case MODE_GAME://�Q�[�����
		InitGame();
		break;

	case MODE_RESULT://���U���g���
		InitResult();
		break;

	case MODE_GAMEOVER://�Q�[���I�[�o�[���
		InitGameover();
		break;

	case MODE_CLEAR://�N���A���
		InitClear();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		InitTutorial();
		break;
	}

	g_mode = mode;
}

//==============================================================
//���[�h�̎擾
//==============================================================
MODE GetMode(void)
{
	return g_mode;
}

//==============================================================
//FPS�̕\��
//==============================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));
}