//====================================================
//
// モーション[motion.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _MOTION_H_
#define _MOTION_H_

// インクルード
#include"main.h"
#include "model.h"
#include <vector>

// 前方宣言
class CInfo;

// モーションクラス
class CMotion
{
public:
	CMotion();
	~CMotion();

	HRESULT Init(CMotion* pMotion);
	HRESULT Init(std::vector<CInfo*> pInfo, std::vector<CModel*> pModel,int NumModel, std::vector<D3DXVECTOR3> OffsetPos, std::vector<D3DXVECTOR3> OffsetRot);
	void Uninit(void);
	void UninitModel(void);
	void Set(int nType);
	void Update(void);
	bool isFinish(void);

	void Stop(void) { m_bStop = true; }
	void Play(void) { m_bStop = false; }

	std::vector<CModel*> GetModel(void)const { return m_apModel; };
	std::vector<CInfo*> GetInfo(void)const { return m_apInfo; };
	D3DXVECTOR3 GetModelPos(int modelindx) { return m_apModel[modelindx]->GetPos(); }
	D3DXVECTOR3 GetCurrentPos(int modelIndx) { return m_CurrentPos[modelIndx]; }
	std::vector<D3DXVECTOR3> GetOffsetPos(void) { return m_OffsetPos; }
	std::vector<D3DXVECTOR3> GetOffsetRot(void) { return m_OffsetRot; }
	int GetNumModel(void) { return m_nNumModel; };
	int GetNumKey(void) { return m_nNumKey; };
	int GetType(void) { return m_nType; };
	int GetFream(void) {return m_nCounter;}
	bool GetFinish(void) { return m_bFinish; };

	void SetInfo(std::vector<CInfo*> pInfo);
	void SetModel(std::vector<CModel*> pModel);
	void SetNumModel(int NumModel) { m_nNumModel = NumModel; };
	void SetNumKey(int NumKey) { m_nNumKey = NumKey; };

private:
	std::vector<CModel*> m_apModel;					// パーツのモデルへのポインタ
	std::vector<CInfo*> m_apInfo;					// モーション情報へのポインタ
	std::vector<D3DXVECTOR3> m_OffsetPos;			// モデルのオフセット（位置）
	std::vector<D3DXVECTOR3> m_OffsetRot;			// モデルのオフセット (角度)
	std::vector<D3DXVECTOR3> m_CurrentPos;			// 現在位置
	std::vector<D3DXVECTOR3> m_CurrentRot;			// 現在の向き
	int m_nNumModel;								// パーツモデル数
	int m_nNumKey;									// キー数
	bool m_bFinish;									// 終了したかどうか
	bool m_bStop;									// モーションを止めるかどうか

	int m_nType;									// 現在の種類
	int m_nTypeOld;									// 前フレームの種類記録用
	int m_nKey;										// 現在のキー
	int m_nNextKey;									// 前のキー
	int m_nCounter;
};
#endif // !_MOTION_H_