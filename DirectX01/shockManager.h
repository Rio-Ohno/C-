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
#include"meshcylinder.h"

#define MAX_POSNUM (3)

// 衝撃波管理クラス
class CShockManager
{
public:
	CShockManager();
	~CShockManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Spawn(int nPatternIndx, int posIndx);
	void Place(int nPatternIndx, int posIndx);
	void AddposNum(void);

private:
	static CShockPattern* m_pPattern;
	static CShockwave* m_apShockWave[SHOCK_NUM];
	static int m_anCntFream[SHOCK_NUM];
	static int m_anPatternIndx[SHOCK_NUM];
	static CMeshCylinder* m_apCylinder[MAX_POSNUM];
	int m_anCntSet;
	D3DXVECTOR3 m_pos[SHOCK_NUM];
};
#endif // !_SHOCKMANAGER_H_