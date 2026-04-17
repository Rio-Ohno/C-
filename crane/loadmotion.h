//====================================================
// 
// モーション情報読込クラス[loadmotion.h]
// Author: Rio Ohno
// 
//====================================================
#ifndef _LOADMOTION_H_
#define _LOADMOTION_H_

// インクルード
#include <vector>

// 前方宣言
class CMotion;
class CModel;
class CInfo;
class CKeyInfo;
class CKEY;
class CLoadtxt;

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

	// constexpr
	static constexpr int NUM_CHAR = 64;

	static CLoadtxt* m_pLoadtxt;					// テキスト読込へのポインタ

	int m_nNumParts;								// パーツ数
	int m_nModelCount;								// モデルのカウント
	int m_nKeyCount;								// パーツのカウント
	int m_nKeyInfoCount;							// キー情報のカウント
	int m_nInfoCount;								// モーション情報のカウント
	std::vector<char*> m_PartPath;					// パーツモデルのパス

	float m_fSpeed;									// 移動量
	float m_fJump;									// ジャンプ量
	float m_fRadiusShaow;							// 影の半径
};
#endif // !_LOADMOTION_H_