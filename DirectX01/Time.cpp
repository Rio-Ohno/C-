//====================================================
// 
// �^�C�}�[����[Time.cpp]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"Time.h"

//====================================================
// �R���X�g���N�^
//====================================================
CTime::CTime()
{
	// �ϐ��̏�����
	m_bTimeOver = false;
	m_bPasses = true;
	m_nDigit = 0;
	m_nCntFrame = 0;
	m_nTimeLim = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CTime::~CTime()
{
	// �Ȃ�
}

//====================================================
// ��������
//====================================================
CTime* CTime::Create(TYPE type, int nMax, int digit, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTime* pTime = NULL;

	// �������̊m��
	pTime = new CTime;

	// �ϐ��̐ݒ�
	pTime->m_type = type;
	pTime->m_nDigit = digit;
	pTime->m_nTimeLim = nMax;

	// ����������
	pTime->Init(pos, fWidth, fHeight);

	return pTime;
}

//====================================================
// ����������
//====================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		pos.x -= (fWidth);

		// �����̐���
		m_apNumber[nCnt] = CNumber::Create(pos, fWidth, fHeight);
	}

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// �����̏I������
			m_apNumber[nCnt]->CNumber::Uninit();
		}
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//====================================================
// �X�V���u
//====================================================
void CTime::Update(void)
{
	// �Q�[���I�[�o�[�ł͂Ȃ��Ȃ�
	if (m_bTimeOver == false)
	{
		if (m_bPasses == true)
		{
			switch (m_type)
			{

			case TYPE_CNTUP:

				// �J�E���g�A�b�v����
				CntUP();

				break;

			case TYPE_CNTDOWN:

				// �J�E���g�_�E������
				CntDown();

				break;

			default:

				break;
			}

			// ���l�̐ݒ菈��
			SetTime();
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// �����̕`�揈��
			m_apNumber[nCnt]->Draw();
		}
	}
}

//====================================================
// �F�̐ݒ菈��
//====================================================
void CTime::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < m_nDigit * 2; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// �F�̐ݒ菈��
			m_apNumber[nCnt]->SetColor(col);
		}
	}
}

//====================================================
// �e�N�X�`���C���f�b�N�X�̊���
//====================================================
void CTime::BindTexIndx(int indx)
{
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// �e�N�X�`���C���f�b�N�X�̐ݒ菈��
			m_apNumber[nCnt]->BindTexindx(indx);
		}
	}
}

//====================================================
// �J�E���g�A�b�v�̍X�V����
//====================================================
void CTime::CntUP(void)
{
	//���ԃJ�E���g
	m_nCntFrame++;

	m_nTime[0] = m_nCntFrame;

	if (m_nTime[0] == 60)
	{
		m_nTime[1]++;
		m_nTime[0] = 0;
		m_nCntFrame = 0;
	}
	if (m_nTime[1] == 60)
	{	
		m_nTime[2]++;
		m_nTime[1] = 0;
	}
}

//====================================================
// �J�E���g�_�E���̍X�V����
//====================================================
void CTime::CntDown(void)
{
	//���ԃJ�E���g(�t���[��)
	m_nCntFrame++;

	m_nTime[0] = m_nTimeLim;

	if (m_nCntFrame == 60)//60�t���[����������
	{
		//��b���炷
		m_nTimeLim--;

		//�t���[���J�E���^�̏�����
		m_nCntFrame = 0;
	}

	if (m_nTimeLim < 0)//�^�C����0�ɂȂ�����
	{
		//�Q�[�����I��点��
		m_bTimeOver = true;
	}
}

//========================================================
// �^�C�}�[�̐ݒ�
//========================================================
void CTime::SetTime(void)
{
	int nDigit = 0;
	int nCntTime1, nCntTime2 = 0;
	int Time[3] = { 0,0,0 };

	if (m_type == TYPE_CNTUP)
	{
		for (nCntTime1 = 0; nCntTime1 < m_nDigit * 0.5f; nCntTime1++)
		{
			Time[nCntTime1] = m_nTime[nCntTime1];
		}
	}
	else if (m_type == TYPE_CNTDOWN)
	{
		Time[0] = m_nTime[0];
	}

	// �\�����l�̐ݒ�
	for (nCntTime1 = 0; nCntTime1 < m_nDigit; nCntTime1++)
	{
		if (m_type == TYPE_CNTUP)
		{
			int n = nCntTime1 / 2;
			int i = m_apNumber[nCntTime1]->SetNum(Time[n], nCntTime1 % 2);
		}
		else
		{
			int i = m_apNumber[nCntTime1]->SetNum(Time[0], nCntTime1);
		}
	}
}