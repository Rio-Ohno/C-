//====================================================
//
// ファンクション(処理をまとめたもの)　[function.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

// 機能基底クラス
class CFunctionBase
{
public:
	CFunctionBase() {}
	virtual ~CFunctionBase() {};

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

private:
};

#endif // !_FUNCTION_H_