//==============================================================
//
//SHOOTING GAME[enemy.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"enemy.h"
#include"explosion.h"
#include"bullet.h"

//�}�N����`
#define NUM_ENEMY (4)//�G�̎��

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];//�G�̏��

//==============================================================
//�G�̏���������
//==============================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��(�G�̎�ޕ�)�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy000.png",
		&g_pTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy100.png",
		&g_pTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy200.png",
		&g_pTextureEnemy[2]);

	//�G�̏��̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;   //g_pTextureEnemy[0];
		g_aEnemy[nCntEnemy].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_aEnemy[nCntEnemy].g_shotcounter = 0;
	}

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(50.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 60.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//�G�̏I������
//==============================================================
void UninitEnemy(void)
{
	//�e�N�X�`��(�G�̎�ޕ�)�̔j��
	if (g_pTextureEnemy[0] != NULL)
	{
		g_pTextureEnemy[0]->Release();
		g_pTextureEnemy[0] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//==============================================================
//�G�̍X�V����
//==============================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;

	Enemy* pEnemy{};
	
	//if ()
	//{
	//	pEnemy->move.x += -1.5f;
	//}

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�e���g�p�����

			//�e�̈ʒu�̍X�V
			//g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].pos;

			//���_���W�̍X�V
			//pVtx[0].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f + 0.125f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].bUse * 0.125f + 0.125f, 1.0f);

			if (g_aEnemy[nCntEnemy].pos.x < 0 - 25)
			{
				g_aEnemy[nCntEnemy].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}

			if (g_aEnemy[nCntEnemy].nLife < 0)
			{
				//�����̐ݒ�
				SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));

				g_aEnemy[nCntEnemy].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}

			g_aEnemy[nCntEnemy].g_shotcounter++;

			if (g_aEnemy[nCntEnemy].g_shotcounter >= rand())
			{
				//�G���e������
				SetBullet(g_aEnemy[nCntEnemy].pos,
					D3DXVECTOR3(-4.5f, 0.0f, 0.0f),//�X�s�[�h(�ړ���)
					100,
					BULLETTYPE_ENEMY);

				g_aEnemy[nCntEnemy].g_shotcounter = 0;
			}

			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);

		}
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	/*Enemy pEnemy;

	pEnemy.move.x += 10.0f;
	pEnemy.move.y += 10.0f;*/

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//�G�̕`�揈��
//==============================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEnemy,
				2);
		}
	}
}

//==============================================================
//�G�̐ݒ菈��
//==============================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ�
			//�G�̏���ݒ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = type;
			g_aEnemy[nCntEnemy].nLife = 120;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25.0f, g_aEnemy[nCntEnemy].pos.y + 25.0f, 0.0f);

			//���_�J���[�̐ݒ�
			g_aEnemy[nCntEnemy].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//==============================================================
//�G�̎擾
//==============================================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}