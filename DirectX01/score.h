//==================================================== 
// 
// �X�R�A�@[score.h]
// Author: Rio Ohno
// 
//==================================================== 
#ifndef _SCORE_H_
#define _SCORE_H_

// �}�N����`
#define MAX_SCOREDIGHT (8)		// �ő包��

// �C���N���[�h
#include"main.h"
#include"Number.h"
#include"object.h"

// �}�N����`
#define SAVEFILE_SCORE ("data\\txt\\score.txt")

class CScore:public CObject
{
public:
	CScore(int nPriority = 7);
	~CScore();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos) {};
	void SetRot(const D3DXVECTOR3 rot) {};
	void SetColor(D3DXCOLOR col);
	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(); };

	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };
	D3DXCOLOR GetColor(void);

	static CScore* Create(D3DXVECTOR3 pos, int nDigit, float fWidth, float fHeight);

	void SetScore(void);
	void BindTexIndx(int nTexIndex);
	void Add(const int nAdd);
	void Diff(const int nDiff);
	void Save(const char* FileName);
	static int Load(const char* FileName);

private:
	CNumber* m_apNumber[MAX_SCOREDIGHT];
	int m_Texindx;
	int m_nDigit;// ����
	int m_nScore;// �X�R�A
};
#endif // !_SCORE_H_

