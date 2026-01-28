//==================================================== 
// 
// スコア　[score.h]
// Author: Rio Ohno
// 
//==================================================== 
#ifndef _SCORE_H_
#define _SCORE_H_

// インクルード
#include"main.h"
#include"Number.h"
#include"object.h"

// スコアクラス
class CScore:public CObject
{
public:
	CScore(int nPriority = 6);
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; };
	void SetColor(D3DXCOLOR col);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXCOLOR GetColor(void);

	static CScore* Create(D3DXVECTOR3 pos, int nDigit, float fWidth, float fHeight);

	void SetScore(void);
	void BindTexIndx(int nTexIndex);
	void Add(const int nAdd);
	void Diff(const int nDiff);
	void Save(void);
	static int Load(void);

private:

	// constexpr
	static constexpr int MAX_SCOREDIGHT = 8;								// 最大桁数
	static constexpr const char* SAVEFILE_SCORE = "data\\txt\\score.txt";	// セーブするファイル名
	static constexpr const char* SAVEFILE_SCOREJSON = "data\\SCRIPT\\json\\Score_Save.json";	// セーブするファイル名

	CNumber* m_apNumber[MAX_SCOREDIGHT];	// 数値表示用のポインタ
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	float m_fWidth;							// ポリゴンの幅
	float m_fHeight;						// ポリゴンの高さ
	int m_Texindx;							// テクスチャインデックス
	int m_nDigit;							// 桁数
	int m_nScore;							// スコア
};
#endif // !_SCORE_H_

