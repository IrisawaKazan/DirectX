//==============================================================
//
//[main.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"input.h"
#include"camera.h"
#include"light.h"
#include"player.h"
#include"polygon.h"
#include"shadow.h"
#include"wall.h"
#include"billboard.h"
#include"bullet.h"
#include"explosion.h"
#include"meshfield.h"
#include"block.h"
#include"meshwall.h"
#include"meshhole.h"

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;            //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3D�f�o�C�X�ւ̃|�C���^

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

	//==============================================================
	//�e��I�u�W�F�N�g�̏���������
	//==============================================================
	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitCamera();
	InitLight();
	InitShadow();
	InitPlayer();
	//InitPolygon();
	InitMeshfield();
	InitWall();
	InitBillboard();
	InitBullet();
	InitExplosion();
	InitBlock();
	InitMeshwall();
	InitMeshhole();

	//SetBillboard(D3DXVECTOR3(0.0f, 50.0f, 200.0f));//��

	//��
	//�� - ��
	SetWall(D3DXVECTOR3(0.0f, WALL_HEIGHT, WALL_WIDTH), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	////�� - ��O
	//SetWall(D3DXVECTOR3(0.0f, WALL_HEIGHT, -WALL_WIDTH), D3DXVECTOR3(-D3DX_PI / 2.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	////�� - ��
	//SetWall(D3DXVECTOR3(-WALL_WIDTH, WALL_HEIGHT, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, -D3DX_PI / 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	////�� - �E
	//SetWall(D3DXVECTOR3(WALL_WIDTH, WALL_HEIGHT, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, D3DX_PI / 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//��(��)
	//�� - ��(��)
	SetWall(D3DXVECTOR3(0.0f, WALL_HEIGHT, WALL_WIDTH), D3DXVECTOR3(-D3DX_PI / 2.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	////�� - ��O(��)
	//SetWall(D3DXVECTOR3(0.0f, WALL_HEIGHT, -WALL_WIDTH), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	////�� - ��(��)
	//SetWall(D3DXVECTOR3(-WALL_WIDTH, WALL_HEIGHT, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, D3DX_PI / 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	////�� - �E(��)
	//SetWall(D3DXVECTOR3(WALL_WIDTH, WALL_HEIGHT, 0.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, -D3DX_PI / 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

	SetBlock(D3DXVECTOR3(0.0f, 0.0f, 100.0f));

	SetBlock(D3DXVECTOR3(100.0f, 0.0f, -50.0f));

	SetBlock(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));
	SetBlock(D3DXVECTOR3(-100.0f, 0.0f, -40.0f));

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void Uninit(void)
{
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

	//==============================================================
	//�e��I�u�W�F�N�g�̏I������
	//==============================================================
	UninitKeyboard();
	UninitCamera();
	UninitLight();
	UninitPlayer();
	//UninitPolygon();
	UninitMeshfield();
	UninitShadow();
	UninitWall();
	UninitBillboard();
	UninitBullet();
	UninitExplosion();
	UninitBlock();
	UninitMeshwall();
	UninitMeshhole();
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
	UpdateCamera();
	UpdateLight();
	UpdatePlayer();
	//UpdatePolygon();
	UpdateMeshfield();
	UpdateShadow();
	UpdateWall();
	UpdateBillboard();
	UpdateBullet();
	UpdateExplosion();
	UpdateBlock();
	UpdateMeshwall();
	UpdateMeshhole();
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
		SetCamera();

		DrawPlayer();
		//DrawPolygon();
		DrawMeshfield();
		DrawBillboard();
		DrawBullet();
		DrawExplosion();
		DrawBlock();
		//DrawWall();
		DrawMeshwall();
		//DrawMeshhole();
		DrawShadow();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}