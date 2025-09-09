//====================================================
// 
// �e�N�X�`�� [texture.h]
// Author:Rio Ohno
// 
//====================================================

// �C���N���[�h
#include"texture.h"
#include"manager.h"

// �ÓI�����o�ϐ�
int CTexture::m_nNumAll = 0;
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEX] = { NULL };

//====================================================
// �R���X�g���N�^
//====================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
	}
}

//====================================================
// �f�X�g���N�^
//====================================================
CTexture::~CTexture()
{
	// �Ȃ�
}

//====================================================
// �e�N�X�`���̓Ǎ�
//====================================================
HRESULT CTexture::Load(void)// �ŏ��Ɋ�����index���ߑł����邽�߂̂���
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < CTexture::TYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̓Ǎ�
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			TexturePass[nCnt],
			&m_apTexture[nCnt])))
		{
			return -1;
		}

		// �����J�E���g�A�b�v
		m_nNumAll++;
	}
	int i = 0;
	return S_OK;
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CTexture::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���|�C���^�̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//====================================================
// �w��̃e�N�X�`���Ǎ�(�o�^)
//====================================================
int CTexture::Register(const char* pFilename)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_nNumAll < MAX_TEX)
	{
		if (pFilename != NULL)
		{
			for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
			{
				if (m_apTexture[nCnt] == NULL)
				{
					if(FAILED(D3DXCreateTextureFromFile(pDevice,
						pFilename,
						&m_apTexture[nCnt])))
					{
						return -1;
					}

					// �����J�E���g�A�b�v
					m_nNumAll++;

					// �C���f�b�N�X��Ԃ�
					return nCnt;
				}
			}
		}
		else
		{
			return -1;
		}

	}
	return -1;
}

//====================================================
// �e�N�X�`���|�C���^�̎擾
//====================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIndx)
{
	// �C���f�b�N�X��0��菬�����Ȃ�
	if (nIndx < 0)
	{
		return NULL;
	}
	else
	{
		return m_apTexture[nIndx];
	}
}