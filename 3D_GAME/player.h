//==============================================================
//
//[player.h]
//Author:Irisawa Kazan
//
//==============================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"
#include"block.h"
#include"model.h"
#include"deadblock.h"
#include"deadblockhighspeed.h"
#include"goalblock.h"
#include"lastblock.h"

//�}�N����`
#define MAX_PTEXTURE (128)
#define MAX_PMOVE (2.0f)
#define MAX_PARTS (2)
#define MAX_KEY (10)
#define MAX_MOTION (5)

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,//�ҋ@
	MOTIONTYPE_MOVE,       //�ړ�
	MOTIONTYPE_ACTION,     //�A�N�V����
	MOTIONTYPE_JUMP,       //�W�����v
	MOTIONTYPE_LANDING,    //���n
	MOTIONTYPE_MAX
}MOTIONTYPE;

//�L�[�\����
typedef struct
{
	float fPosX;//�ʒuX
	float fPosY;//�ʒuY
	float fPosZ;//�ʒuZ
	float fRotX;//����X
	float fRotY;//����Y
	float fRotZ;//����Z
}KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;         //�Đ��t���[��
	KEY aKey[MAX_PARTS];//�e�p�[�c�̃L�[�v�f
}KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;                //���[�v���邩�ǂ���
	int nNumKey;               //�L�[�̑���
	KEY_INFO aKeyInfo[MAX_KEY];//�L�[���
}MOTION_INFO;

//�v���C���[�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;                    //�ʒu
	D3DXVECTOR3 posOld;                 //�O��̈ʒu
	D3DXVECTOR3 size;                   //�傫��
	D3DXVECTOR3 move;                   //�ړ���
	D3DXVECTOR3 rot;                    //����
	D3DXVECTOR3 rotDest;                //�ڕW�̌���
	D3DXVECTOR3 vtxMin;                 //���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;                 //���f���̍ő�l
	LPD3DXMESH pMesh;                   //���b�V��(���_���W)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;              //�}�e���A���ւ̃|�C���^
	D3DXMATRIX mtxWorld;                //���[���h�}�g���b�N�X
	DWORD dwNumMat;                     //�}�e���A���̐�
	int nCounterState;                  //��ԊǗ��J�E���^�[
	int nIdxShadow;	                    //�e�̔ԍ�
	bool bDisp;                         //�\�����邩���Ȃ���
	bool bJump;                         //�W�����v�����ǂ���
	bool bRightMove;                    //�E�������Ă��邩�ǂ���
	Model aModel[MAX_PARTS];            //���f��(�p�[�c)
	int nNumModel;                      //���f��(�p�[�c)�̑���
	MOTION_INFO aMotionInfo[MAX_MOTION];//���[�V�������
	int nNumMotion;                     //���[�V�����̑���
	MOTIONTYPE motionType;              //���[�V�����̎��
	bool bLoopMotion;                   //���[�v���邩�ǂ���
	int nNumKey;                        //�L�[�̑���
	int nKey;                           //���݂̃L�[No.
	int nCounterMotion;                 //���[�V�����̃J�E���^�[
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif