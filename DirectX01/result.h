//====================================================
//
// ���U���g�V�[������ [result.h]
// Author:Rio Ohno
//
//====================================================

#ifndef _RESULT_H_
#define _RESULT_H_

// �C���N���[�h
#include"main.h"
#include"scene.h"

class CResult :public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};
#endif // !_TITLE_H_
#pragma once
