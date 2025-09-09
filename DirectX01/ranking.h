//====================================================
//
// �����L���O�V�[������ [ranking.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _RANKING_H_
#define _RANKING_H_

// �C���N���[�h
#include"main.h"
#include"scene.h"
#include"score.h"

// �}�N����`
#define NUM_RANK (5)
#define DISPLAY_FREAM (1200)

// �����L���O�N���X
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

	static void SetMode(CRanking::MODE mode) { m_mode = mode; };
	static CRanking::MODE GetMode(void) { return m_mode; };

private:
	static CScore* m_apScore[NUM_RANK];
	static CRanking::MODE m_mode;
	int m_nScore[NUM_RANK];
	int m_nCntFream;
};

#endif