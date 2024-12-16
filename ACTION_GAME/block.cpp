//==============================================================
//
//ACTION_GAME[block.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"player.h"
#include"block.h"

//�}�N����`
#define MAX_BLOCK (/*128*/61)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;//���_�o�b�t�@�̃|�C���^
Block g_aBlock[MAX_BLOCK];                     //�u���b�N�̏��

//==============================================================
//�u���b�N�̏���������
//==============================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block200.png",
		&g_pTextureBlock);

	//�u���b�N�̏��̏�����
	for (nCntBlock = 0 ; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���
		g_aBlock[nCntBlock].fWidth = 25.0f; //�g�p���Ă��Ȃ���Ԃɂ���
		g_aBlock[nCntBlock].fHeight = 50.0f;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
		pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
		pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
		pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
		pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
		pVtx[3].pos.z = 0.0f;

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
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//�u���b�N�̏I������
//==============================================================
void UninitBlock(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//==============================================================
//�u���b�N�̍X�V����
//==============================================================
void UpdateBlock(void)
{
	int nCntBlock;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[3].pos.z = 0.0f;
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//�u���b�N�̕`�揈��
//==============================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBlock);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N�̎g�p����Ă���
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				4 * nCntBlock, 
				2);
		}
	}
}

//==============================================================
//�u���b�N�̐ݒ菈��
//==============================================================
void SetBlock(D3DXVECTOR3 pos)
{
	int nCntBlock;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//�u���b�N�̎g�p����Ă��Ȃ�
			g_aBlock[nCntBlock].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - 25.0f;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + 25.0f;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + 50.0f;
			pVtx[3].pos.z = 0.0f;

			g_aBlock[nCntBlock].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//==============================================================
//�u���b�N�̏Փˏ��� X
//==============================================================
void CollisionBlockX(D3DXVECTOR3* pPos,//���݂̈ʒu
	D3DXVECTOR3* pPosOld,              //�O��̈ʒu
	D3DXVECTOR3* pMove,                //�ړ���
	float fWidth,                      //��
	float fHeight)                     //����
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//�u���b�N�̍��E�̓����蔻��
			if (pPosOld->y > g_aBlock[nCntBlock].pos.y &&
				pPosOld->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{
				//�u���b�N�̍�����E�ւ̓����蔻��
				if (pPosOld->x + fWidth / 2.0f <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2.0f &&
					pPos->x + fWidth / 2.0f > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2.0f)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - fWidth / 2.0f - g_aBlock[nCntBlock].fWidth / 2.0f;
					pMove->x = 0.0f;
				}
				//�u���b�N�̉E���獶�ւ̓����蔻��
				if (pPosOld->x - fWidth / 2.0f >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2.0f &&
					pPos->x - fWidth / 2.0f < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2.0f)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x + fWidth / 2.0f + g_aBlock[nCntBlock].fWidth / 2.0f;
					pMove->x = 0.0f;
				}
			}
		}
	}
}

//==============================================================
//�u���b�N�̏Փˏ��� Y
//==============================================================
bool CollisionBlockY(D3DXVECTOR3* pPos,//���݂̈ʒu
	D3DXVECTOR3* pPosOld,              //�O��̈ʒu
	D3DXVECTOR3* pMove,                //�ړ���
	float fWidth,                      //��
	float fHeight)                     //����
{
	bool bLanding = false;//���n���Ă��邩�ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//�u���b�N�̏㉺�̓����蔻��
			if (pPos->x + fWidth / 2.0f > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2.0f &&
				pPos->x - fWidth / 2.0f < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2.0f)
			{
				//�u���b�N�̏ォ�牺�ւ̓����蔻��
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y &&
					pPos->y > g_aBlock[nCntBlock].pos.y)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;
				}
				//�u���b�N�̉������ւ̓����蔻��
				else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight;
					pMove->y = 0.0f;
				}
			}
		}
	}
	return bLanding;
}