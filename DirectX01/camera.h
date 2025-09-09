//====================================================
//
//�J����[camera.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

// �C���N���[�h
#include"main.h"
//#include"player.h"


// �J�����N���X
class CCamera
{
public:

	typedef enum
	{
		TYPE_NOMAL = 0,
		TYPE_ASSENT,
		TYPE_MAX
	}TYPE;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void SetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR);
	void SetType(TYPE type);
	void SetRotation(D3DXVECTOR3 rot);

	D3DXVECTOR3 GetRot(void) { return m_rot; };

private:
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_posVDest;		// ���_�̖ڕW�l
	D3DXVECTOR3 m_posRDest;		// �����_�̖ڕW�l
	D3DXVECTOR3 m_vecU;			// �x�N�g��
	D3DXVECTOR3 m_rot;			// ����
	D3DXMATRIX m_mtxProjection;
	D3DXMATRIX m_mtxView;
	TYPE m_type;
	float m_fDistance;
	bool m_bAssent;
};

#endif // !_CAMERA_H_

