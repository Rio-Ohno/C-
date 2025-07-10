//====================================================
//
// ����[explosion.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

// �C���N���[�h
#include"main.h"
#include"object2D.h"

// �}�N����`
#define EXPLOSION_ANIME_SPAN (4)

// �����N���X
class CExplosion :public  CObject2D
{
public:
	//CExplosion();
	CExplosion(int nPriority = 4);
	~CExplosion();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Anime(int nDiviX, int nDiviY);

	static HRESULT Load(void);
	static void UnLoad(void);

	static CExplosion* Create(D3DXVECTOR3 pos, float fRadius);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nCntAnime;			// �t���[���J�E���^�[
	int m_nPatternAnime;		// �p�^�[���J�E���^�[
};

#endif // !_EXPLOSION_H_
