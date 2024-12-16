//==============================================================
//
//SHOOTING GAME[bullet.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"

//�}�N����`
#define MAX_BULLET (128)//�e�̍ő吔

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move;//�ړ���
	int nLife;       //����
	BULLETTYPE type; //���
	bool bUse;       //�g�p���Ă��邩�ǂ���
}Bullet;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_�o�b�t�@�̃|�C���^
Bullet g_aBullet[MAX_BULLET];                   //�e�̏��

//==============================================================
//�e�̏���������
//==============================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//�e�̏��̏�����
	for (nCntBullet = 0 ; nCntBullet < MAX_BULLET ; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_aBullet[nCntBullet].type = {};
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();
}

//==============================================================
//�e�̏I������
//==============================================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//==============================================================
//�e�̍X�V����
//==============================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p�����
			Enemy* pEnemy;//�G�̏��ւ̃|�C���^
			int nCntEnemy;

			Player* pPlayer;
			int nCntPlayer;

			//�G�̎擾
			pEnemy = GetEnemy();

			pPlayer = GetPlayer();

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{//�G���g�p����Ă���
						if (g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + 40.0f/*�E*/
							&& g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - 40.0f/*��*/
							&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - 55.0f/*��*/
							&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + 55.0f/*��*/)
						{
							//�����̐ݒ�
							SetExplosion(pEnemy->pos, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

							pEnemy->bUse = false;              //�G���g�p���Ă����Ԃɂ���
							g_aBullet[nCntBullet].bUse = false;//�G���g�p���Ă����Ԃɂ���
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				for (nCntPlayer = 0; nCntPlayer < 1; nCntPlayer++, pPlayer++)
				{
					if (pPlayer->bDisp == true)
					{//�g�p����Ă���
						if (g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + 40.0f/*�E*/
							&& g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - 40.0f/*��*/
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - 40.0f/*��*/
							&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + 40.0f/*��*/)
						{
							//�����̐ݒ�
							SetExplosion(pPlayer->pos, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

							pPlayer->bDisp = false;            //�g�p���Ă����Ԃɂ���
							g_aBullet[nCntBullet].bUse = false;//�g�p���Ă����Ԃɂ���
						}
					}
				}
			}

			//�e�̈ʒu�̍X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);				

			if (g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 25)
			{
				g_aBullet[nCntBullet].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}

			//�����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].nLife < 0)
			{
				//�����̐ݒ�
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

				g_aBullet[nCntBullet].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}

			/*if (g_aBullet[nCntBullet].type == 0)
			{
				float fRotMove, fRotDest, fRotDiff;
				fRotMove = atan2f(g_aBullet->pos.y, g_aBullet->pos.x);
				fRotDest = atan2f(pEnemy->pos.y, pEnemy->pos.x);
				fRotDiff = fRotDest - fRotMove;//�ڕW�̈ړ������܂ł̊p�x

				//�p�x�̒l���C������
				
				
				fRotMove += fRotDiff * 0.2f;//�ړ������̑��x
			
				//�p�x�̒l���C������
				

				g_aBullet[nCntBullet].move.x = sinf(fRotMove) * 3;
				g_aBullet[nCntBullet].move.y = cosf(fRotMove) * 3;
			}*/
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				4 * nCntBullet, 
				2);
		}
	}
}

//==============================================================
//�e�̐ݒ菈��
//==============================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 25.0f, g_aBullet[nCntBullet].pos.y + 25.0f, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 300;
			g_aBullet[nCntBullet].bUse = true;//�g�p���Ă����Ԃɂ���
			g_aBullet[nCntBullet].type = type;

			break;
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}