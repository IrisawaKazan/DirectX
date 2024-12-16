//==============================================================
//
//SHOOTING GAME[effect.cpp]
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
#include"effect.h"

//�}�N����`
#define MAX_EFFECT (4096)//�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;  //�F
	float fRedius;  //���a(�傫��)
	int nLife;      //����
	bool bUse;      //�g�p���Ă��邩�ǂ���
}Effect;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//���_�o�b�t�@�̃|�C���^
Effect g_aEffect[MAX_EFFECT];                   //�G�t�F�N�g�̏��

//==============================================================
//�G�t�F�N�g�̏���������
//==============================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//�G�t�F�N�g�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fRedius = 0.25;
		g_aEffect[nCntEffect].nLife = 100;
		g_aEffect[nCntEffect].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
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
	g_pVtxBuffEffect->Unlock();
}

//==============================================================
//�G�t�F�N�g�̏I������
//==============================================================
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//==============================================================
//�G�t�F�N�g�̍X�V����
//==============================================================
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			Enemy* pEnemy;//�G�̏��ւ̃|�C���^
			int nCntEnemy;

			//�G�̎擾
			pEnemy = GetEnemy();

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			{
				if (pEnemy->bUse == true)
				{//�G���g�p����Ă���
					//if (/*�G�ƒe����������*/)
					//{
					//	//�����̐ݒ�
					//	SetExplosion(/*�ʒu*/, /*�F*/);

					//	pEnemy->bUse = false;              //�G���g�p���Ă����Ԃɂ���
					//	g_aBullet[nCntBullet].bUse = false;//�G���g�p���Ă����Ԃɂ���
					//}
				}
			}

			//g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].col;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);

			if (g_aEffect[nCntEffect].pos.x > SCREEN_WIDTH + 25)
			{
				g_aEffect[nCntEffect].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}

			//�����̃J�E���g�_�E��
			g_aEffect[nCntEffect].nLife--;

			if (g_aEffect[nCntEffect].nLife < 0)
			{
				//�����̐ݒ�
				SetExplosion(g_aEffect[nCntEffect].pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f));

				g_aEffect[nCntEffect].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//==============================================================
//�G�t�F�N�g�̕`�揈��
//==============================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEffect,
				2);
		}
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==============================================================
//�G�t�F�N�g�̐ݒ菈��
//==============================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife)
{
	int nCntEffect;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;

			/*//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 25.0f, g_aEffect[nCntEffect].pos.y + 25.0f, 0.0f);*/

			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRedius = fRedius;
			g_aEffect[nCntEffect].nLife = 300;
			g_aEffect[nCntEffect].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}

		//pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}