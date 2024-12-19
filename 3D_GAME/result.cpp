//==============================================================
//
//3D_GAME[result.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"result.h"

//�O���[�o���ϐ��錾
RESULT g_result = RESULT_1;//���݂̃��[�h

//==============================================================
//���U���g��ʂ̏���������
//==============================================================
void InitResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		InitResultFirst();
		break;

	case RESULT_2:
		InitResultSecond();
		break;

	case RESULT_3:
		InitResultThird();
		break;
	}
}

//==============================================================
//���U���g��ʂ̏I������
//==============================================================
void UninitResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		UninitResultFirst();
		break;
	}
}

//==============================================================
//���U���g��ʂ̍X�V����
//==============================================================
void UpdateResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		UpdateResultFirst();
		break;

	case RESULT_2:
		UpdateResultSecond();
		break;

	case RESULT_3:
		UpdateResultThird();
		break;
	}
}

//==============================================================
//���U���g��ʂ̕`�揈��
//==============================================================
void DrawResult(void)
{
	switch (g_result)
	{
	case RESULT_1:
		DrawResultFirst();
		break;

	case RESULT_2:
		DrawResultSecond();
		break;

	case RESULT_3:
		DrawResultThird();
		break;
	}
}

//==============================================================
//���U���g��ʂ̐ݒ�
//==============================================================
void SetResult(RESULT result)
{
	g_result = result;
}

//==============================================================
//���U���g��ʂ̎擾
//==============================================================
RESULT GetResult(void)
{
	return g_result;
}