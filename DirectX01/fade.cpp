//====================================================
//
//�t�F�[�h����[fade.cpp]
//Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"fade.h"
#include"manager.h"

//====================================================
// �R���X�g���N�^
//====================================================
CFade::CFade()
{
	// �ϐ��̏�����
	m_fade = FADE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);        //�����|���S���i�s�����j�ɂ��Ă���
	m_pVtxBuff = { NULL };
}

//====================================================
// �f�X�g���N�^
//====================================================
CFade::~CFade()
{
	// �Ȃ�
}

//====================================================
// ����������
//====================================================
HRESULT CFade::Init(void)
{
	m_fade = FADE_IN;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);        //�����|���S���i�s�����j�ɂ��Ă���

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx{};

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�o�b�t�@�̐����A���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//====================================================
// �X�V����
//====================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			//�t�F�[�h�C���̏��
			m_colorFade.a -= 0.02f;

			if (m_colorFade.a < 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			//�t�F�[�h�A�E�g���
			m_colorFade.a += 0.02f;

			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				//���[�h�ݒ�i���̉�ʂɈڍs�j
				CManager::SetMode(m_modeNext);
			}
		}

		VERTEX_2D* pVtx{};

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//====================================================
// �`�揈��
//====================================================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̃f�[�^�X�g���[����ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================================================
//�t�F�[�h�̐ݒ菈��
//=============================================================================================================
void CFade::Set(CScene::MODE modeNext)
{
	m_fade = FADE_OUT;                                                         //�t�F�[�h�A�E�g��Ԃ�
	m_modeNext = modeNext;                                                     //���̉�ʂ�ݒ�
}

//=============================================================================================================
//�t�F�[�h�̎擾����
//=============================================================================================================
CFade::FADE CFade::Get(void)
{
	return m_fade;
}