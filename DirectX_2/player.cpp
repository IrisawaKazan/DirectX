//==============================================================
//
//SHOOTING GAME[player.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"bullet.h"
#include"enemy.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//���_�o�b�t�@�̃|�C���^
int g_nCounterAnimPlayer;                       //�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;                       //�A�j���[�V�����p�^�[��No.
D3DXVECTOR3 g_movePlayer;                       //�ړ���
D3DXVECTOR3 g_rotPlayer;                        //����
float g_fLengthPlayer;                          //�Ίp���̒���
float g_fAnglePlayer;                           //�Ίp���̊p�x
Player g_player;                                //�v���C���[�̏��
//VERTEX_2D g_aVertex[4];                         //���_�����i�[

//==============================================================
//�v���C���[�̏���������
//==============================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice, 
		"data\\TEXTURE\\player000.png", 
		&g_pTexturePlayer);

	//player000.png

	g_nCounterAnimPlayer = 0;                       //�J�E���^�[������������
	g_nPatternAnimPlayer = 0;                       //�p�^�[��No.������������
	g_player.pos = D3DXVECTOR3(75.0f, 360.0f, 0.0f);//�ʒu������������(�����ʒu)
	g_movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //�ړ��ʂ�����������
	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //����������������

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf(200.0f * 200.0f + 300.0f * 300.0f) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(200.0f, 300.0f);

	g_player.bDisp = true;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer, 
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	/*//���_���W�̐ݒ�
	g_aVertex[0].pos = D3DXVECTOR3(450.0f, 150.0f, 0.0f);
	g_aVertex[1].pos = D3DXVECTOR3(850.0f, 150.0f, 0.0f);
	g_aVertex[2].pos = D3DXVECTOR3(450.0f, 550.0f, 0.0f);
	g_aVertex[3].pos = D3DXVECTOR3(850.0f, 550.0f, 0.0f);

	//rhw�̐ݒ�
	g_aVertex[0].rhw = 1.0f;
	g_aVertex[1].rhw = 1.0f;
	g_aVertex[2].rhw = 1.0f;
	g_aVertex[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	g_aVertex[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aVertex[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aVertex[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aVertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	/*g_aVertex[0].col = D3DCOLOR_RGBA(0, 255, 200, 255);
	g_aVertex[1].col = D3DCOLOR_RGBA(0, 255, 200, 255);
	g_aVertex[2].col = D3DCOLOR_RGBA(0, 255, 200, 255);*/

	/*//�e�N�X�`�����W�̐ݒ�
	g_aVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_aVertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_aVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_aVertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);*/
}

//==============================================================
//�v���C���[�̏I������
//==============================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//==============================================================
//�v���C���[�̍X�V����
//==============================================================
void UpdatePlayer(void)
{
	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�������ꂽ
			if (GetKeyboardPress(DIK_W) == true)
			{//A�L�[��W�L�[���������ꂽ
				g_movePlayer.x += sinf(D3DX_PI * -0.75f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * -0.75f) * 0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//A�L�[��S�L�[���������ꂽ
				g_movePlayer.x += sinf(D3DX_PI * -0.25f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * -0.25f) * 0.5f;
			}
			else
			{
				g_movePlayer.x -= 0.5f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�������ꂽ
			if (GetKeyboardPress(DIK_W) == true)
			{//D�L�[��W�L�[���������ꂽ
				g_movePlayer.x += sinf(D3DX_PI * 0.75f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * 0.75f) * 0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//D�L�[��S�L�[���������ꂽ
				g_movePlayer.x += sinf(D3DX_PI * 0.25f) * 0.5f;
				g_movePlayer.y += cosf(D3DX_PI * 0.25f) * 0.5f;
			}
			else
			{
				g_movePlayer.x += 0.5f;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�������ꂽ
			g_movePlayer.y -= 0.5f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[�������ꂽ
			g_movePlayer.y += 0.5f;
		}
		/*else if (GetKeyboardPress(DIK_Z) == true)
		{//Z�L�[�������ꂽ
			g_rotPlayer.z += 0.0375f;
		}
		else if (GetKeyboardPress(DIK_X) == true)
		{//X�L�[�������ꂽ
			g_rotPlayer.z -= 0.0375f;
		}*/
		/*else if (GetKeyboardPress(DIK_E) == true)
		{//E�L�[�������ꂽ
			g_fAnglePlayer += 0.0375f;
		}
		else if (GetKeyboardPress(DIK_R) == true)
		{//R�L�[�������ꂽ
			g_fAnglePlayer -= 0.0375f;
		}*/
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{//SPACE�L�[�������ꂽ
			//�e�̐ݒ�
			SetBullet(g_player.pos,
				D3DXVECTOR3(5.0f, 0.0f, 0.0f),//�X�s�[�h(�ړ���)
				100,
				BULLETTYPE_PLAYER);
		}

		//g_nCounterAnimPlayer++;//�J�E���^�[���v�Z
		VERTEX_2D* pVtx{};       //���_���ւ̃|�C���^

		/*//�A�j���[�V����
		if (g_nCounterAnimPlayer % 15 == 0)
		{
			g_nCounterAnimPlayer = 0;                             //�J�E���^�[�������l�ɖ߂�
			g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 1;//�p�^�[��No.���X�V����

			//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.125f + 0.125f, 1.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}*/

		//�ʒu���X�V
		g_player.pos.x += g_movePlayer.x;
		g_player.pos.y += g_movePlayer.y;

		//�ړ��ʂ��X�V(����������)
		g_movePlayer.x += (0.0f - g_movePlayer.x) * 0.085f;
		g_movePlayer.y += (0.0f - g_movePlayer.y) * 0.085f;

		//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̍X�V
		pVtx[0].pos.x = g_player.pos.x + sinf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_player.pos.y + cosf(g_rotPlayer.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_player.pos.x + sinf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_player.pos.y + cosf(g_rotPlayer.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}

//==============================================================
//�v���C���[�̕`�揈��
//==============================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		/*pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
			2,                                       //�v���~�e�B�u(�|���S��)��
			&g_aVertex[0],                           //���_���̐擪�f�o�C�X
			sizeof(VERTEX_2D));                      //���_���\���̂̃T�C�Y*/
	}
}

//==============================================================
//�v���C���[�̃q�b�g����
//==============================================================
void HitPlayer(int nDamage)
{

}

//==============================================================
//�v���C���[�̎擾����
//==============================================================
Player* GetPlayer(void)
{
	return &g_player;
}