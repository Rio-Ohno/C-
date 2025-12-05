//====================================================
//
//フェード処理[fade.h]
//Author:Rio Ohno
//
//====================================================

#ifndef _FADE_H_
#define _FADE_H_

// インクルード
#include"main.h"
#include"scene.h"

// フェードクラス
class CFade
{
public:

	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,//真っ暗
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade();
	~CFade();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CScene::MODE modeNext);
	FADE Get(void);
	
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;              // 頂点バッファへのポインタ
	FADE m_fade;                                     // フェードの状態
	CScene::MODE m_modeNext;                         // 次の画面（モード）
	D3DXCOLOR m_colorFade;                           // ポリゴン（フェード）の色
};
#endif // !_FADE_H_

