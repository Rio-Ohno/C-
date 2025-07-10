//====================================================
//
// �I�u�W�F�N�g[object.cpp]
// Author:Rio Ohno
//
//====================================================

//�C���N���[�h
#include "object.h"
#include"manager.h"
#include"camera.h"

//�ÓI�����o�ϐ�
int CObject::m_nNumAll = 0;
CObject* CObject::m_pTop[PRIORITY] = { NULL };
CObject* CObject::m_pCur[PRIORITY] = { NULL };

////====================================================
//// �R���X�g���N�^
////====================================================
//CObject::CObject()
//{
//	//�l���N���A����
//	m_nID = 0;
//	m_type = TYPE_NONE;
//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
//	{
//		if (m_apObject[nCnt] == NULL)
//		{
//			m_apObject[0][nCnt] = this;//�������g����
//			m_nPriority = 0;// ���g�̗D�揇�ʂ�ۑ�
//			m_nID = nCnt;// ���g��ID��ۑ�
//			m_nNumAll++;// �����J�E���g�A�b�v
//			break;
//		}
//	}
//}

//====================================================
// �R���X�g���N�^
//====================================================
CObject::CObject(int nPriority)
{
	//�l���N���A����
	m_type = TYPE_NONE;
	m_bDeath = false;			// ���S�t���O�̏�����
	m_nPriority = nPriority;	// ���g�̗D�揇�ʂ�ۑ�
	m_nNumAll++;				// �����J�E���g�A�b�v

	// �擪�̃|�C���^���Ȃ��Ȃ�
	if (m_pTop[nPriority] == NULL)
	{
		// �擪�ɑ������
		m_pTop[nPriority] = this;
	}

	// �Ō���̃|�C���^���Ȃ��Ȃ�
	if (m_pCur[nPriority] == NULL)
	{
		// �Ō���ɑ������
		m_pCur[nPriority] = this;
	}

	// ���g���Ō���ɂȂ�Ȃ�
	else
	{
		// ���g��O�̃|�C���^�̎��ɐݒ�
		m_pCur[nPriority]->m_pNext = this;

		// ���g�̑O�̃|�C���^�̐ݒ�
		this->m_pPrev = m_pCur[nPriority];

		// ���g�̎��̃|�C���^��������
		this->m_pNext = { NULL };

		// ���M���Ō���ɂ���
		m_pCur[nPriority] = this;
	}
}

//====================================================
// �f�X�g���N�^
//====================================================
CObject::~CObject()
{
	
}

//====================================================
// �S�ẴI�u�W�F�N�g�̔j��
//====================================================
void CObject::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		CObject* pObject = m_pTop[nPriority];	// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{
			// ���̃|�C���^��ۑ�
			CObject* pObNext = pObject->m_pNext;

			// �X�V����
			pObject->Uninit();

			// ���̃I�u�W�F�N�g����
			pObject = pObNext;
		}

		// ���S�t���O���������I�u�W�F�N�g������
		CObject::Delete(nPriority);
	}
}

//====================================================
// �S�ẴI�u�W�F�N�g�̍X�V����
//====================================================
void CObject::UpdateAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		CObject* pObject = m_pTop[nPriority];	// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{
			// ���̃|�C���^��ۑ�
			CObject* pObNext = pObject->m_pNext;

			// �X�V����
			pObject->Update();

			// ���̃I�u�W�F�N�g����
			pObject = pObNext;
		}

		// ���S�t���O���������I�u�W�F�N�g������
		CObject::Delete(nPriority);
	}
}

//====================================================
// �S�ẴI�u�W�F�N�g�̕`�揈��
//====================================================
void CObject::DrawAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		CObject* pObject = m_pTop[nPriority];	// �擪�̃I�u�W�F�N�g����

		while (pObject != nullptr)
		{
			// ���̃|�C���^��ۑ�
			CObject* pObNext = pObject->m_pNext;

			// �X�V����
			pObject->Draw();

			// ���̃I�u�W�F�N�g����
			pObject = pObNext;
		}
	}

	// �J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	// �J�����̐ݒ�
	pCamera->SetCamera();
}

//====================================================
// �I�u�W�F�N�g�̎��S�t���O�𗧂Ă�
//====================================================
void CObject::Release(void)
{
	// ���g�̎��S�t���O�𗧂Ă�
	this->m_bDeath = true;
}

//====================================================
// ���S�t���O���������I�u�W�F�N�g�̔j��
//====================================================
void CObject::Delete(int nPriority)
{
	CObject* pObject = m_pTop[nPriority];

	while (pObject != NULL)
	{
		// ���̃|�C���^��ۑ�
		CObject* pObNext = pObject->m_pNext;

		if (pObject->m_bDeath == true)
		{
			// �擪�����g�Ȃ�
			if (m_pTop[nPriority] == pObject)
			{
				// ���̃|�C���^�����݂���Ȃ�
				if (pObject->m_pNext != nullptr)
				{
					// ���g�̎��̃|�C���^��擪�̃|�C���^�ɂ���
					m_pTop[nPriority] = pObject->m_pNext;

					// �擪�̃|�C���^�̑O�̃|�C���^�����X�g�������
					m_pTop[nPriority]->m_pPrev = { nullptr };
				}

				// ���g�݂̂Ȃ�
				else
				{
					// �擪�̃|�C���^����ɂ���
					m_pTop[nPriority] = { nullptr };
				}
			}

			// �Ō�������g�Ȃ�
			else if (m_pCur[nPriority] == pObject)
			{
				// �O�̃|�C���^�����݂���Ȃ�
				if (pObject->m_pPrev != nullptr)
				{
					// ���g�̑O�̃|�C���^���Ō���̃|�C���^�ɂ���
					m_pCur[nPriority] = pObject->m_pPrev;

					// �Ō���̃|�C���^�̎��̃|�C���^�����X�g�������
					m_pCur[nPriority]->m_pNext = { nullptr };
				}
			}

			// ���g���擪�ł��Ō���ł��Ȃ��Ȃ�
			else
			{
				// ���g�̉��ۑ�
				CObject* pObjectKeep = pObject;

				// ���g�̑O�̃|�C���^�̎��̃|�C���^�����g�̎��̃|�C���^�ɐݒ�
				pObject->m_pPrev->m_pNext = pObjectKeep->m_pNext;

				// ���g�̎��̃|�C���^�̑O�̃|�C���^�����g�̑O�̃|�C���^�ɐݒ�
				pObject->m_pNext->m_pPrev = pObjectKeep->m_pPrev;

				//// ���ۑ��������̂��폜<-������ʖڂ������Bthis���Ə����Ă�
				//delete pObject;
			}

			// �������̊J��(���g�̔j��)
			delete pObject;

			// ���������炷
			m_nNumAll--;
		}

		// ���̃I�u�W�F�N�g����
		pObject = pObNext;
	}
}

//====================================================
// ��ނ̐ݒ�
//====================================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//====================================================
// ��ނ̎擾
//====================================================
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}

//====================================================
// �I�u�W�F�N�g�̎擾
//====================================================
CObject* CObject::GetObject(int nPriority, int nindx)
{
	return /*m_apObject[nPriority][nindx]*/NULL;
}

//====================================================
// �I�u�W�F�N�g�̑���
//====================================================
int CObject::GetNumAll(void)
{
	return m_nNumAll;
}