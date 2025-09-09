//====================================================
// 
// �Ռ��g[shockwave.h]
// Author:Rio Ohno
// 
//==================================================== 

#ifndef _SHOCKWAVE_H_
#define _SHOCKWAVE_H_

// �C���N���[�h
#include"main.h"
#include"object.h"

class CShockwave:public CObject
{
public:
	CShockwave();
	~CShockwave();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DXCOLOR col,bool bTransparent);
	void SetVanish(int nfream);
	void SetCulling(bool bUse) { m_bCulling = bUse; };

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };
	bool isCulling(void) { return m_bCulling; };
	bool isCollision(D3DXVECTOR3 pos, float fRadius, float fUnder, float fTop);

	void Spread(void);						// �L���鉉�o����
	void Vanish(void);						// �����鉉�o����

	static CShockwave* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY,int nLife, float fWidth, float fHeight, float fRadius, float fSpeed, bool bCulling, bool bCollision);

private:

	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	int m_nTexindx;							// �e�N�X�`���C���f�b�N�X
	int m_nDiviX;							// ������(x��)
	int m_nDiviY;							// ������(y��)
	int m_nMaxVtx;							// �ő咸�_��
	int m_nPolyNum;							// �|���S����
	int m_nLife;							// ����
	int m_nVanishFream;						// ������t���[����(�ۑ��p)
	int m_nVanishCnt;						// ������t���[���J�E���^�[
	float m_fHeight;						// ����
	float m_fWidth;							// ��
	float m_fRadius;						// ���a
	float m_fSpeed;							// �L����X�s�[�h
	bool m_bCulling;						// �J�����O���邩�ǂ���
	bool m_bCollision;						// �����蔻����Ƃ邩�ǂ���
	bool m_bVanish;							// �����鉉�o�����邩�ǂ���
};

#endif // !_SHOCKWAVE_H_