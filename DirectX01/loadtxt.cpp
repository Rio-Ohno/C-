//====================================================
//
// txt�Ǎ�[loadtxt.cpp]
// Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"loadtxt.h"
#include <stdlib.h>

//====================================================
// �R���X�g���N�^
//====================================================
CLoadtxt::CLoadtxt()
{
	// �Ȃ�
}

//====================================================
// �f�X�g���N�^
//====================================================
CLoadtxt::~CLoadtxt()
{
	// �Ȃ�
}

//====================================================
// �V���[�v�ȍ~���΂�����
//====================================================
void CLoadtxt::SkipComment(FILE* pFile)
{
	char cData[2] = {};
	char cData1[128] = {};

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a)// ���s�R�[�h�ł͂Ȃ��Ȃ�
		{
			strcat(cData1, cData);
		}
		else
		{
			break;
		}
	}
}

//====================================================
//  = ��ǂݔ�΂�����
//====================================================
void CLoadtxt::SkipEqual(FILE* pFile)
{
	int nData;
	nData = fgetc(pFile);
	nData = fgetc(pFile);
	nData = fgetc(pFile);
}

//====================================================
// �󔒂�ǂݔ�΂�����
//====================================================
void CLoadtxt::SkipBlank(FILE* pFile)
{
	char nData;
	nData = (char)fgetc(pFile);

	int i = 0;
}

//====================================================
// ������ǂݍ��ޏ���
//====================================================
int CLoadtxt::LoadInt(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	int nData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			nData = atoi(cData1);// char�^����int�^��
			cData1[0] = { NULL };
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return nData;
}

//====================================================
// ����������ǂݍ��ޏ���
//====================================================
float CLoadtxt::LoadFloat(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	float fData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			fData = (float)atof(cData1); // char�^����double�^->float�^��
			cData1[0] = { NULL };
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return fData;
}

//====================================================
// ������^��ǂݍ��ޏ���
//====================================================
char* CLoadtxt::LoadPath(FILE* pFile, char* cData2)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char filepath[32] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != 0x23 && cData[0] != 0x20 && cData[0] != 0x09)// ���s # �� tab����Ȃ��Ȃ�
		{
			strcat(cData1, cData);
		}
		else
		{
			cData2 = cData1;
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return cData2;
}