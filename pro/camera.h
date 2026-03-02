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

// カメラクラス
class CCamera
{
public:

	typedef enum
	{
		TYPE_NOMAL = 0,	// ノーマル
		TYPE_ASSENT,	// 追従
		TYPE_MAX
	}TYPE;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Follow(const D3DXVECTOR3 TargetPos,const D3DXVECTOR3 TargetRot);
	void Follow(void);

	// セッター
	void SetCamera(void);
	void SetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR);
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }
	void SetType(TYPE type);
	void SetRotation(D3DXVECTOR3 rot);
	void SetFollowTarget(const D3DXVECTOR3 TargetPos, const D3DXVECTOR3 TargetRot) { m_posTarget = TargetPos; m_rotTarget = TargetRot; }

	// ゲッター
	D3DXVECTOR3 GetRot(void) { return m_rot; };

private:

	// constexpr
	static constexpr float FOLLOW_DECAY = 0.09f;	// 追従中の減衰係数
	static constexpr float MOVE = 1.0f;				// 移動量
	static constexpr float TURN = 0.01f;			// 旋回量

	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_posVDest;		// 視点の目標値
	D3DXVECTOR3 m_posRDest;		// 注視点の目標値
	D3DXVECTOR3 m_posTarget;	// 追従時のターゲットの位置
	D3DXVECTOR3 m_rotTarget;	// 追従時のターゲットの向き
	D3DXVECTOR3 m_vecU;			// ベクトル
	D3DXVECTOR3 m_rot;			// 向き
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		// ビューマトリックス
	TYPE m_type;				// 種類
	float m_fDistance;			// 視点と注視点間の距離
	bool m_bAssent;				// 追従するかどうか
};

#endif // !_CAMERA_H_

