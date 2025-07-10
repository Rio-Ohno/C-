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

// �e�N�X�`���p�X
const char* TexturePass[] =
{
	"data\\TEXTURE\\BG001.jpg",
	"data\\TEXTURE\\bg101.png",
	"data\\TEXTURE\\bg102.png",
	"data\\TEXTURE\\fish.png",
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\suraimu100.png",
	"data\\TEXTURE\\cat001.png",
	"data\\TEXTURE\\explosion000.png"
	"data\\TEXTURE\\number001.png",
};

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

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̓Ǎ�
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			TexturePass[nCnt],
			&m_apTexture[nCnt])))
		{
			return -1;
		}
		m_nNumAll++;
	}
	return S_OK;
}

//====================================================
// �e�N�X�`���̔j��
//====================================================
void CTexture::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
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

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (pFilename != NULL)
		{
			if (m_apTexture[nCnt] == NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pFilename,
					&m_apTexture[nCnt]);

				m_nNumAll++;

				return nCnt;
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
	if (nIndx < 0 || nIndx == NULL)
	{
		return NULL;
	}
	else
	{
		return m_apTexture[nIndx];
	}
}