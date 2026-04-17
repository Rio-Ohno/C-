//====================================================
// 
// モーション情報クラス[motionInfo.h]
// Author:Rio Ohno
// 
//====================================================
#ifndef _MOTIONINFO_H_
#define _MOTIONINFO_H_
 
// インクルード
#include "main.h"
#include<vector>

// 前方宣言
class CModel;
class CInfo;

// モーション情報クラス
class CMotionInfo
{
public:
	CMotionInfo();
	CMotionInfo(const CMotionInfo& other);
	~CMotionInfo() {};

	void Uninit(void);
	void UninitModel(void);

	std::vector<CModel*> GetModel(void) { return m_apModel; };
	std::vector<CInfo*> GetInfo(void) { return m_apInfo; };
	std::vector<D3DXVECTOR3> GetOffsetPos(void) { return m_OffsetPos; }
	std::vector<D3DXVECTOR3> GetOffsetRot(void) { return m_OffsetRot; }
	int GetNumModel(void) { return m_nNumModel; };

	void SetInfo(std::vector<CInfo*> pInfo);
	void SetModel(std::vector<CModel*> pModel);
	void SetNumModel(int NumModel) { m_nNumModel = NumModel; };

private:

	std::vector<CInfo*> m_apInfo;					// モーション情報へのポインタ
	std::vector<CModel*> m_apModel;					// パーツのモデルへのポインタ
	std::vector<D3DXVECTOR3> m_OffsetPos;
	std::vector<D3DXVECTOR3> m_OffsetRot;
	int m_nNumModel;								// パーツモデル数
};
#endif // !_MOTIONINFO_H_