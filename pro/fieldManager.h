//====================================================
//
// フィールドマネージャー [fieldManager.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _FIELDMANAGER_H_
#define _FIELDMANAGER_H_

// インクルード
#include "meshfield.h"

// フィールドマネージャークラス
class CFiledManager
{
public:
	CFiledManager();
	~CFiledManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetWave(D3DXVECTOR3 pos, float fWidth, float fHeight, float fRadius,float fSpeed, int nLifeSeccond, float fAttenuation);
	void UpdateWave(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void BindFiled(CMeshField* pFiled) { m_pMeshField = pFiled; };

private:

	void Reset(void);

	static CMeshField* m_pMeshField;	// メッシュフィールド格納用
	D3DXVECTOR3 m_pos;					// 発生位置
	int m_nCntFream;					// フレームカウンター
	int m_nLifeFream;					// 寿命（フレーム）
	float m_fHeight;					// 高さ
	float m_fWidth;						// 幅
	float m_fRadius;					// 半径
	float m_fSpeed;						// 速さ
	float m_fAttenuation;				// 減衰
	bool m_bFinish;						// 終わっているかどうか
};
#endif // !_FIELDMANAGER_H_