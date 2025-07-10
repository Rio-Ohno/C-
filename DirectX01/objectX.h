//====================================================
//
// Xファイル[objectX.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

// インクルード
#include"main.h"
#include"object.h"

// マクロ定義
#define MAX_MAT (512) 

// Xファイルクラス
class CObjectX :public CObject
{
public:
	CObjectX();
	virtual ~CObjectX();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void BindModel(const char* pFileName);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };

	LPD3DXMESH GetMesh(void) { return m_pMesh; };
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };

	static CObjectX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
	int m_anTexIndx[MAX_MAT];					// テクスチャポインタのインデックス保存用
	LPD3DXMESH m_pMesh;							// メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;					// マテリアルへのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	DWORD m_dwNumMat;							// マテリアルの数
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	bool m_bExistence = false;					// モデルの有無
};

#endif
