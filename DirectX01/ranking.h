//====================================================
//
// ランキングシーン処理 [ranking.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _RANKING_H_
#define _RANKING_H_

// インクルード
#include"main.h"
#include"scene.h"
#include"score.h"

// マクロ定義
#define NUM_RANK (5)
#define DISPLAY_FREAM (1200)
#define SAVEFILE_RANKING ("data\\txt\\ranking.txt")

// ランキングクラス
class CRanking : public CScene
{
public:

	typedef enum
	{
		MODE_NONE = 0,
		MODE_DISPLAY,
		MODE_GAME,
		MODE_MAX
	}MODE;

	CRanking();
	~CRanking();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Load(const char* FileName);
	void Save(const char* FileName);
	void Sort(void);
	void Flashing(void);
	void Reset(void);

	static void SetMode(CRanking::MODE mode) { m_mode = mode; };
	static CRanking::MODE GetMode(void) { return m_mode; };

private:
	static CScore* m_apScore[NUM_RANK];
	static CRanking::MODE m_mode;
	int m_anScore[NUM_RANK];
	int m_nRank;
	int m_nCntFream;
	int m_nCntFreamColor;
	bool m_bFlashing;// 点滅させるかどうか
};

#endif