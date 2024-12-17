//==============================================================
//
//3D_GAME[title.cpp]
//Author:Irisawa Kazan
//
//==============================================================
#include"title.h"

//�O���[�o���ϐ��錾
TITLE g_title = TITLE_1;//���݂̃��[�h

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
void InitTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		InitTitlefirst();
		break;

	case TITLE_2:
		InitTitlesecond();
		break;

	case TITLE_3:
		InitTitlethird();
		break;
	}
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void UninitTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		UninitTitlefirst();
		break;
	}
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void UpdateTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		UpdateTitlefirst();
		break;

	case TITLE_2:
		UpdateTitlesecond();
		break;

	case TITLE_3:
		UpdateTitlethird();
		break;
	}
}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void DrawTitle(void)
{
	switch (g_title)
	{
	case TITLE_1:
		DrawTitlefirst();
		break;

	case TITLE_2:
		DrawTitlesecond();
		break;

	case TITLE_3:
		DrawTitlethird();
		break;
	}
}

//==============================================================
//�^�C�g���̐ݒ�
//==============================================================
void SetTitle(TITLE title)
{
	g_title = title;
}

//==============================================================
//�^�C�g���̎擾
//==============================================================
TITLE GetTitle(void)
{
	return g_title;
}