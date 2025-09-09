//====================================================
//
//カメラ[camera.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

// インクルード
#include"main.h"
//#include"player.h"


// カメラクラス
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
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_posVDest;		// 視点の目標値
	D3DXVECTOR3 m_posRDest;		// 注視点の目標値
	D3DXVECTOR3 m_vecU;			// ベクトル
	D3DXVECTOR3 m_rot;			// 向き
	D3DXMATRIX m_mtxProjection;
	D3DXMATRIX m_mtxView;
	TYPE m_type;
	float m_fDistance;
	bool m_bAssent;
};

#endif // !_CAMERA_H_

