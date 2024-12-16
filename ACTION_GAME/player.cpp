//==============================================================
//
//ACTION_GAME[player.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"block.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//���_�o�b�t�@�̃|�C���^
int g_nCounterAnimPlayer;                       //�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;                       //�A�j���[�V�����p�^�[��No.
float g_fLengthPlayer;                          //�Ίp���̒���
float g_fAnglePlayer;                           //�Ίp���̊p�x
Player g_player;                                //�v���C���[�̏��

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

	g_nCounterAnimPlayer = 0;                                                     //�J�E���^�[������������
	g_nPatternAnimPlayer = 0;                                                     //�p�^�[��No.������������
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT - 50.0f, 0.0f);//�ʒu������������(�����ʒu)
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                                //�ړ��ʂ�����������
	g_player.posOld = D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT - 50.0f, 0.0f);
	g_player.state = {};
	g_player.nCounterState = {};
	g_player.bJump = {};
	g_player.bRightMove = {};
	g_player.pBlock = NULL;

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf(100.0f * 100.0f + 150.0f * 150.0f) / 2.0f;

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
	pVtx[0].pos.x = g_player.pos.x - 50.0f;
	pVtx[0].pos.y = g_player.pos.y - 150.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + 50.0f;
	pVtx[1].pos.y = g_player.pos.y - 150.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x - 50.0f;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + 50.0f;
	pVtx[3].pos.y = g_player.pos.y;
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
	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
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
	g_nCounterAnimPlayer++;//�J�E���^�[���v�Z
	VERTEX_2D* pVtx{};     //���_���ւ̃|�C���^

	if (g_player.bDisp == true)
	{
		//���Ɉړ�����
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT) == true)
		{//A�L�[�������ꂽ
			g_player.move.x -= 1.0f;

			//�A�j���[�V����
			if ((g_nCounterAnimPlayer % 7 == 0) && g_player.bJump == false)
			{
				g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;//�p�^�[��No.���X�V����

				//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 1.0f);
			}
		}
		//�E�Ɉړ�����
		else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) == true)
		{//D�L�[�������ꂽ
			g_player.move.x += 1.0f;

			//�A�j���[�V����
			if ((g_nCounterAnimPlayer % 7 == 0) && g_player.bJump == false)
			{
				g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;//�p�^�[��No.���X�V����

				//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f + 0.25f, 0.5f);
			}
		}
		//�u���b�N�Ƃ̍��E�̓����蔻��
		CollisionBlockX(&g_player.pos, &g_player.posOld, &g_player.move, 100.0f, 150.0f);
		//�u���b�N�Ƃ̏㉺�̓����蔻��
		if (CollisionBlockY(&g_player.pos, &g_player.posOld, &g_player.move, 100.0f, 150.0f) == true)
		{
			g_player.bJump = false;
		}
		////���R�������ɃW�����v���ł��Ȃ�����
		//if (g_player.move.y == true )
		//{
		//	g_player.bJump = true;
		//}
		//�W�����v����
		if ((GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_UP) == true) && g_player.bJump == false/* && g_player.move.y == false*/)
		{
			g_player.move.y = -21.0f;
			g_player.bJump = true;
		}
		//�u���b�N���o��
		/*if ((GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) == true) && g_player.bJump == false)
		{//S�L�[�������ꂽ
			SetBlock(D3DXVECTOR3(g_player.pos.x + 75.0f, g_player.pos.y - 50.0f, 0.0f));
		}*/
		if (GetKeyboardTrigger(DIK_Q) == true && g_player.bJump == false)
		{//Q�L�[�������ꂽ
			SetBlock(D3DXVECTOR3(g_player.pos.x - 75.0f, g_player.pos.y - 50.0f, 0.0f));
		}
		if (GetKeyboardTrigger(DIK_E) == true && g_player.bJump == false)
		{//E�L�[�������ꂽ
			SetBlock(D3DXVECTOR3(g_player.pos.x + 75.0f, g_player.pos.y - 50.0f, 0.0f));
		}

		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		//if (g_player.pBlock != NULL)
		//{//�u���b�N�ɏ���Ă���
		//	g_player.pBlock
		//}

		//�ʒu���X�V
		g_player.pos.x += g_player.move.x;//���ړ�
		g_player.pos.y += g_player.move.y;//����

		g_player.move.y += 0.98f;         //�d�͉��Z

		////�ŏI�I�ɂ͏���(��)
		//if (g_player.pos.y >= SCREEN_HEIGHT)
		//{
		//	g_player.pos.y = SCREEN_HEIGHT;
		//	g_player.move.y = 0.0f;
		//	g_player.bJump = false;
		//	//g_player.bDisp = false;
		//}

		//�ړ��ʂ��X�V(����������)
		g_player.move.x += (0.0f - g_player.move.x) * 0.25f;

		//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_player.pos.x - 50.0f;
		pVtx[0].pos.y = g_player.pos.y - 150.0f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_player.pos.x + 50.0f;
		pVtx[1].pos.y = g_player.pos.y - 150.0f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_player.pos.x - 50.0f;
		pVtx[2].pos.y = g_player.pos.y;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_player.pos.x + 50.0f;
		pVtx[3].pos.y = g_player.pos.y;
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