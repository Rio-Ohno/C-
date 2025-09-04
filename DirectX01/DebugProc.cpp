//====================================================
// 
// �f�o�b�N�\�� [DebugProc.cpp]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"DebugProc.h"
#include"manager.h"
#include <stdio.h>

// �ÓI�����o�ϐ�
LPD3DXFONT CDebugProc::m_pFont = { NULL };
char CDebugProc::m_aStr[MAX_STRING] = { NULL };
bool CDebugProc::m_bDisp = false;

//====================================================
// �R���X�g���N�^
//====================================================
CDebugProc::CDebugProc()
{
	// �Ȃ�
}

//====================================================
// �f�X�g���N�^
//====================================================
CDebugProc::~CDebugProc()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
void CDebugProc::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(pDevice,
		25, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"���C���I",
		&m_pFont);

	//�f�o�b�O�\�����̃N���A
	memset(&m_aStr[0], NULL, sizeof(m_aStr));

// �����\���ݒ�
#if _DEBUG
	m_bDisp = true;
#else NDEBUG
	m_bDisp = false;
#endif
}

//====================================================
// �I������
//====================================================
void CDebugProc::Uninit(void)
{
	// �t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//====================================================
// �X�V����
//====================================================
void CDebugProc::Update(void)
{
#ifdef _DEBUG

	// �L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard != NULL)
	{
		// �f�o�b�N�\���̕\����\��
		if (pKeyboard->GetTrigger(DIK_1) == true)
		{
			m_bDisp = m_bDisp ? false : true;
		}
	}
#endif // DEBUG
}

//====================================================
// �`�揈��
//====================================================
void CDebugProc::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	RECT rect = { 10,20,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (m_bDisp == true)
	{
		//�e�L�X�g�̕`��
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 200, 125, 255));
	}

	//�f�o�b�O�\�����̃N���A
	memset(&m_aStr[0], NULL, sizeof(m_aStr));
}

//====================================================
// �o�͏���
//====================================================
void CDebugProc::Print(const char* fmt, ...)
{
	va_list args;
	char aString[MAX_STRING];
	char aproStr[MAX_STRING];
	int nLength = 0;
	int nStopLength;

	// ���������
	strcpy(&aString[0], fmt);

	// �ϒ��������X�g�̏������J�n
	va_start(args, fmt);

	for (char* s = &aString[0]; *s != '\0'; s++)
	{
		if (*s == '%')
		{
			// �^�w�������
			s++;

			switch (*s)
			{
			case 'd':	// ����

				// ������Ƃ��ĕϊ�
				sprintf(&aproStr[0], "%d", va_arg(args, int));

				// ������̒������擾
				nLength = (int)strlen(&aproStr[0]);

				break;

			case 'f':

				// ������Ƃ��ĕϊ�
				sprintf(&aproStr[0], "%f", va_arg(args, double));

				// ������̒������擾
				nLength = (int)strlen(&aproStr[0]);

				//�����_�ȉ��̕����ڂ܂Ŋm�F
				for (int nCntlength = 0; aproStr[nCntlength] != '\0'; nCntlength++)
				{
					if (aproStr[nCntlength] == '.')
					{//�����_���������ꍇ

						//�����_�ȉ��̌��������߂�
						int nMin = (int)strlen(&aproStr[nCntlength + 1]);

						//�����_����̕������Ǝw�肵���l�܂ł̍��������߂�
						nMin -= MAX_FLOATNUM;

						//������̒����������_�ȉ����ʂ܂łɕ␳
						nLength -= nMin;
					}
				}

				break;

			case 'c':

				// ������Ƃ��ĕϊ�
				sprintf(&aproStr[0], "%c", va_arg(args, char));

				// ������̒������擾
				nLength = (int)strlen(&aproStr[0]);

				break;

			case 's':

				// ������Ƃ��ĕϊ�
				vsnprintf(&aproStr[0], sizeof(aproStr), "%s", args);

				//������̒������擾
				nLength = (int)strlen(&aproStr[0]);

				break;

			default:
				break;
			}

			nStopLength = (int)strlen(s) + 1;

			//���������̊m�F���������̕���������炷
			memmove(s + nLength - 2, s, nStopLength);

			s--;	//�|�C���^��%�܂Ŗ߂�

			//�ψ������w�肳�ꂽ�ꏊ�ɑ}��
			memcpy(s, &aproStr[0], nLength);

		}
	}

	va_end(args);

	//�������A������
	strcat(&m_aStr[0], &aString[0]);
}