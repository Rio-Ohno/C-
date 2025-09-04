//====================================================
// 
// 衝撃波の管理処理 [shockManager.h]
// Author:Rio Ohno
// 
//====================================================

#ifndef _SHOCKMANAGER_H_
#define _SHOCKMANAGER_H_

// インクルード
#include"main.h"
#include"loadshock.h"
#include"shockwave.h"

// 衝撃波管理クラス
class CShockManager
{
public:
	CShockManager();
	~CShockManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Spawn(int nPatternIndx);
	void Place(int nPatternIndx, int posIndx);

private:
	static CShockPattern* m_pPattern;
	static CShockwave* m_apShockWave[SHOCK_NUM];
	static int m_anCntFream[SHOCK_NUM];
	static int m_anPatternIndx[SHOCK_NUM];
	D3DXVECTOR3 m_pos[SHOCK_NUM];
};
#endif // !_SHOCKMANAGER_H_