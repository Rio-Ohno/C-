//====================================================
//
// モーション[motion.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _MOTION_H_
#define _MOTION_H_

// インクルード
#include "main.h"
#include"loadtxt.h"
#include"key.h"
#include"model.h"
#include <string.h>
#include <stdio.h>

// マクロ定義
#define MAX_PART (20)
#define MAX_MOTION (8)

// モーションクラス
class CMotion
{
public:
	CMotion();
	~CMotion();

	HRESULT Init(CMotion* pMotion);
	HRESULT Init(CInfo** pInfo, CModel** pModel,int NumModel,D3DXVECTOR3* OffsetPos,D3DXVECTOR3* OffsetRot);
	void Uninit(void);
	void UninitModel(void);
	void Set(int nType);
	void Update(void);
	bool isFinish(void);

	void Stop(void) { m_bStop = true; }
	void Play(void) { m_bStop = false; }

	CModel** GetModel(void) { return m_apModel; };
	CInfo** GetInfo(void) { return m_apInfo; };
	D3DXVECTOR3 GetModelPos(int modelindx) { return m_apModel[modelindx]->GetPos(); }
	D3DXVECTOR3 GetCurrentPos(int modelIndx) { return m_CurrentPos[modelIndx]; }
	D3DXVECTOR3* GetOffsetPos(void) { return m_OffsetPos; }
	D3DXVECTOR3* GetOffsetRot(void) { return m_OffsetRot; }
	int GetNumModel(void) { return m_nNumModel; };
	int GetNumKey(void) { return m_nNumKey; };
	int GetType(void) { return m_nType; };
	int GetFream(void) {return m_nCounter;}
	bool GetFinish(void) { return m_bFinish; };

	void SetInfo(CInfo** pInfo);
	void SetModel(CModel** pModel);
	void SetNumModel(int NumModel) { m_nNumModel = NumModel; };
	void SetNumKey(int NumKey) { m_nNumKey = NumKey; };

private:
	CModel* m_apModel[MAX_PART];					// パーツのモデルへのポインタ
	CInfo* m_apInfo[MAX_MOTION];					// モーション情報へのポインタ
	D3DXVECTOR3 m_OffsetPos[MAX_PART];
	D3DXVECTOR3 m_OffsetRot[MAX_PART];
	D3DXVECTOR3 m_CurrentPos[MAX_PART];				// 現在位置
	D3DXVECTOR3 m_CurrentRot[MAX_PART];				// 現在の向き
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

// モーション情報クラス
class CMotionInfo
{
public:
	CMotionInfo();
	CMotionInfo(const CMotionInfo& other);
	~CMotionInfo() {};

	void Uninit(void);
	void UninitModel(void);

	CModel** GetModel(void) { return m_apModel; };
	CInfo** GetInfo(void) { return m_apInfo; };
	D3DXVECTOR3* GetOffsetPos(void) { return m_OffsetPos; }
	D3DXVECTOR3* GetOffsetRot(void) { return m_OffsetRot; }
	int GetNumModel(void) { return m_nNumModel; };

	void SetInfo(CInfo** pInfo);
	void SetModel(CModel** pModel);
	void SetNumModel(int NumModel) { m_nNumModel = NumModel; };

private:

	CInfo* m_apInfo[MAX_MOTION];					// モーション情報へのポインタ
	CModel* m_apModel[MAX_PART];					// パーツのモデルへのポインタ
	int m_nNumModel;								// パーツモデル数
	D3DXVECTOR3 m_OffsetPos[MAX_PART];
	D3DXVECTOR3 m_OffsetRot[MAX_PART];
};

// モーション読込クラス
class CLoadMotion
{
public:
	CLoadMotion();
	~CLoadMotion();

	void LoadMotionTXT(const char* pFileName, CMotion* pMotion);
	void LoadMotion(FILE* pFile, CMotion* pMotion);
	void LoadCharacterInfo(FILE* pFile, CMotion* pMotion);
	CModel* LoadModel(FILE* pFile, CMotion* pMotion);
	CInfo* LoadInfo(FILE* pFile);
	CKeyInfo* LoadKeyInfo(FILE* pFile);
	CKEY* LoadKey(FILE* pFile);

	static CMotion* Load(const char* pFileName, CMotion* pMotion);

private:
	static CLoadtxt* m_pLoadtxt;					// テキスト読込へのポインタ

	int m_nNumParts;								// パーツ数

	int m_nModelCount;
	int m_nKeyCount;								// パーツのカウント
	int m_nKeyInfoCount;							// キー情報のカウント
	int m_nInfoCount;								// モーション情報のカウント
	char m_PartPath[MAX_PART][64];					// パーツモデルのパス

	float m_fSpeed;									// 移動量
	float m_fJump;									// ジャンプ量
	float m_fRadiusShaow;							// 影の半径
};
#endif // !_MOTION_H_
