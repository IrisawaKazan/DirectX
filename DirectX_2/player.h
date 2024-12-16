//==============================================================
//
//SHOOTING GAME[player.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _PLAYER_H_//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_//2�d�C���N���[�h�h�~�̃}�N����`

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//�o�����
	PLAYERSTATE_NORMAL,    //�ʏ�
	PLAYERSTATE_DAMAGE,    //�_���[�W
	PLAYERSTATE_DEATH,     //���S

	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 move; //�ړ���
	PLAYERSTATE state;//�v���C���[�̏��
	int nCounterState;//��ԊǗ��J�E���^�[
	int nLife;        //�̗�
	bool bDisp;       //�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
Player* GetPlayer(void);

#endif