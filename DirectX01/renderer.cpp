//====================================================
//
// �����_���[[renderer.cpp]
// Author:Rio Ohno
//
//====================================================

//�C���N���[�h
#include "renderer.h"
#include"manager.h"
#include"input.h"
#include "object.h"

// �ÓI�����o�ϐ�
CSound* CRenderer::m_pSound = { NULL };

//====================================================
// �R���X�g���N�^
//====================================================
CRenderer::CRenderer()
{
	//�N���A�ɂ���
	m_pD3D = NULL;
	m_pD3DDevice = NULL;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apTexMT[nCnt] = NULL;
	}
}

//====================================================
// �f�X�g���N�^
//====================================================
CRenderer::~CRenderer()
{

}

//====================================================
// ����������
//====================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;             //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;      //�v���[���e�[�V�����p�����[�^

	//DirectX3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));                               // �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                            // �Q�[����ʂ̃T�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                          // �Q�[����ʂ̃T�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;                           // �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                       // �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                        // �_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;                             // �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                       // �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;                                        // �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//DirectX3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�s���j
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DirectX3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs���j
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//========================================================
	// �}���`�^�[�Q�b�g�����_�����O
	// =======================================================
	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̐���
	m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
								SCREEN_HEIGHT, 
								1, 
								D3DUSAGE_RENDERTARGET,
								D3DFMT_A8R8G8B8, 
								D3DPOOL_DEFAULT, 
								&m_pTexMT, 
								NULL);

	// �e�N�X�`���C���^�[�t�F�[�X�̐���
	m_pTexMT->GetSurfaceLevel(0, &m_pRenderMT);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̐���
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_apTexMT[nCnt],
			NULL);

		// �e�N�X�`���C���^�[�t�F�[�X�̐���
		m_apTexMT[nCnt]->GetSurfaceLevel(0, &m_apRenderMT[nCnt]);

	}

	// �e�N�X�`�������_�����O�pZ�o�b�t�@�̐���
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, 
											SCREEN_HEIGHT, 
											D3DFMT_D16, 
											D3DMULTISAMPLE_NONE, 
											0, 
											TRUE, 
											&m_pZBuffMT, 
											NULL);

	// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// ���݂�z�o�b�t�@���擾(�ۑ�)
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

	// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT);

	// z�o�b�t�@�𐶐�����z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �����_�����O�p�e�N�X�`���̃N���A
	m_pD3DDevice->Clear(0,
						NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 0), 
						1.0f, 
						0);

	// �����_�����O�^�[�Q�b�g�����ɖ߂�
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// z�o�b�t�@�����ɖ߂�
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// �e�N�X�`�������_�����O�p�r���[�|�[�g�̐ݒ�
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;

	//���_�o�b�t�@�̐���
	m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMT,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//rhw�̐ݒ�
		pVtx[nCnt].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffMT->Unlock();

	//----------------------------------
	// �T�E���h
	//----------------------------------

	// �������̊m��
	m_pSound = new CSound;

	// ������
	m_pSound->Init(hWnd);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CRenderer::Uninit(void)
{
	//========================================================
	// �e��I�u�W�F�N�g�̏I������
	// =======================================================

	// �e�N�X�`���̔j��
	if (m_pTexMT != NULL)
	{
		m_pTexMT->Release();
		m_pTexMT = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apTexMT[nCnt] != NULL)
		{
			m_apTexMT[nCnt]->Release();
			m_apTexMT[nCnt] = NULL;
		}
	}

	if (m_pSound != NULL)
	{
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//DirectX3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//DirectX3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//====================================================
// �X�V����
//====================================================
void CRenderer::Update(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard* pKeyboard = CManager::GetKeyboard();

	//========================================================
	// �e��I�u�W�F�N�g�̍X�V����
	//========================================================
	CObject::UpdateAll();

#if _DEBUG

	if (pKeyboard->GetTrigger(DIK_F2) == true)// ���C���[�t���[���ɂ���
	{
		CRenderer::onWireFrame();
	}
	else if (pKeyboard->GetTrigger(DIK_F1) == true)// ���C���[�t���[����؂�
	{
		CRenderer::offWireFrame();
	}

#endif
}

//====================================================
// �`�揈��
//====================================================
void CRenderer::Draw(void)
{
	LPDIRECT3DSURFACE9 pRenderWk;
	LPDIRECT3DTEXTURE9 pTexWk;

	// �o�b�N�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
	m_pD3DDevice->GetRenderTarget(0, &pRenderWk);

	//// �t�B�[�h�o�b�N�G�t�F�N�g������Ȃ�
	//if (isFeedbackEffect() == true)
	//{
	//	//// �����_�����O�^�[�Q�b�g���e�N�X�`��[0]�ɐݒ�
	//	//m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);
	//}
	//else if (isFeedbackEffect() == false)
	//{
	//
	//}

	// �e�N�X�`��[0]�̃N���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�j
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//�`��J�n�����������ꍇ

	//========================================================
	// �e��I�u�W�F�N�g�̕`�揈��
	//========================================================
	
		//�S�ẴI�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();

		//���_���ւ̃|�C���^
		VERTEX_2D* pVtx = NULL;

		//���_�o�b�t�@�����b�N
		m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.99f);
		}

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuffMT->Unlock();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(VERTEX_2D));

		//�e�N�X�`���̐ݒ�
		m_pD3DDevice->SetTexture(0, m_apTexMT[1]);

		//���_�t�H�[�}�b�g�̐ݒ�
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		//�|���S���̕`��
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// �����_�����O�^�[�Q�b�g�����ɖ߂�
		m_pD3DDevice->SetRenderTarget(0, pRenderWk);

		//���_�o�b�t�@�����b�N
		m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuffMT->Unlock();

		//�e�N�X�`���̐ݒ�
		m_pD3DDevice->SetTexture(0, m_apTexMT[0]);

		//�|���S���̕`��
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	// �e�N�X�`�������ς���
	pTexWk = m_apTexMT[0];
	m_apTexMT[0] = m_apTexMT[1];
	m_apTexMT[1] = pTexWk;

	pRenderWk = m_apRenderMT[0];
	m_apRenderMT[0] = m_apRenderMT[1];
	m_apRenderMT[1] = pRenderWk;
}

//====================================================
// �f�o�C�X�̎擾
//====================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)const
{
	return m_pD3DDevice;
}

//====================================================
// �����_�����O�^�[�Q�b�g�̕ύX
//====================================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect;

	// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT);

	//// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	//m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	// z�o�b�t�@�𐶐�����z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �e�N�X�`�������_�����O�p�̃r���[�|�[�g��ݒ�
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̐���
	fAspect = (float)m_viewportMT.Width / (float)m_viewportMT.Height;

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection, 
								D3DXToRadian(45.0f),
								fAspect,
								10.0f,
								1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}