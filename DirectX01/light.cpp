//====================================================
//
//���C�g[light.cpp]
//Author:Rio Ohno
//
//====================================================

// �C���N���[�h
#include"light.h"
#include"manager.h"

//====================================================
// �R���X�g���N�^
//====================================================
CLight::CLight()
{
	// �Ȃ�
}

//====================================================
// �f�X�g���N�^
//====================================================
CLight::~CLight()
{
	// �Ȃ�
}

//====================================================
// ���C�g�̏���������
//====================================================
HRESULT CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];//���C�g�̕����x�N�g��
	D3DXCOLOR vecDif[MAX_LIGHT];//���C�g�̕����x�N�g��

	//���C�g���N���A
	ZeroMemory(&m_light, sizeof(m_light));

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̎�ނ�ݒ�
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;//���s����
	}

	//���C�g�̊g�U����ݒ�
	//vecDif[0] = D3DXCOLOR(1.0f, 1.0f, 0.8f, 1.0f);
	//vecDif[1] = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	//vecDif[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	vecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̊g�U����ݒ�
		m_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//����������
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		m_light[nCnt].Direction = vecDir[nCnt];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_light[nCnt]);

	}

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	return S_OK;
}

//====================================================
// ���C�g�̏I������
//====================================================
void CLight::Uninit(void)
{

}

//====================================================
// ���C�g�̍X�V����
//====================================================
void CLight::Update(void)
{

}
