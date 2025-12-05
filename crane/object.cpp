//====================================================
//
// オブジェクト[object.cpp]
// Author:Rio Ohno
//
//====================================================

//インクルード
#include "object.h"
#include"manager.h"
#include"camera.h"

//静的メンバ変数
int CObject::m_nNumAll = 0;
bool CObject::m_bPause = false;
CObject* CObject::m_pTop[PRIORITY] = { NULL };
CObject* CObject::m_pCur[PRIORITY] = { NULL };

//====================================================
// コンストラクタ
//====================================================
CObject::CObject(int nPriority)
{
	//値をクリアする
	m_type = TYPE_NONE;
	m_bDeath = false;			// 死亡フラグの初期化
	m_nPriority = nPriority;	// 自身の優先順位を保存
	m_nNumAll++;				// 総数カウントアップ

	// 先頭のポインタがないなら
	if (m_pTop[nPriority] == NULL)
	{
		// 先頭に代入する
		m_pTop[nPriority] = this;
		this->m_pPrev = { NULL };
	}

	// 最後尾のポインタがないなら
	if (m_pCur[nPriority] == NULL)
	{
		// 最後尾に代入する
		m_pCur[nPriority] = this;
		this->m_pNext = { NULL };
	}

	// 自身が最後尾になるなら
	else
	{
		// 自身を前のポインタの次に設定
		m_pCur[nPriority]->m_pNext = this;

		// 自身の前のポインタの設定
		this->m_pPrev = m_pCur[nPriority];

		// 自身の次のポインタを初期化
		this->m_pNext = { NULL };

		// 自信を最後尾にする
		m_pCur[nPriority] = this;
	}
}

//====================================================
// デストラクタ
//====================================================
CObject::~CObject()
{
	// 総数を減らす
	m_nNumAll--;
}

//====================================================
// 全てのオブジェクトの破棄
//====================================================
void CObject::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		CObject* pObject = m_pTop[nPriority];	// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{
			// 次のポインタを保存
			CObject* pObNext = pObject->m_pNext;

			// 更新処理
			pObject->Uninit();

			// 次のオブジェクトを代入
			pObject = pObNext;
		}

		// 死亡フラグがたったオブジェクトを消す
		CObject::Delete(nPriority);
	}
}

//====================================================
// 全てのオブジェクトの更新処理
//====================================================
void CObject::UpdateAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		CObject* pObject = m_pTop[nPriority];	// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{
			// 次のポインタを保存
			CObject* pObNext = pObject->m_pNext;

			if (m_bPause == false)
			{
				// 更新処理
				pObject->Update();
			}
			else
			{
				// ポーズのタグまたはシーンのタグが付いているなら
				if (pObject->m_type == TYPE_PAUSE || pObject->m_type == TYPE_SCENE)
				{
					// 更新処理
					pObject->Update();
				}
			}

			// 次のオブジェクトを代入
			pObject = pObNext;
		}

		// 死亡フラグがたったオブジェクトを消す
		CObject::Delete(nPriority);
	}
}

//====================================================
// 全てのオブジェクトの描画処理
//====================================================
void CObject::DrawAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		CObject* pObject = m_pTop[nPriority];	// 先頭のオブジェクトを代入

		while (pObject != nullptr)
		{
			// 次のポインタを保存
			CObject* pObNext = pObject->m_pNext;

			// 更新処理
			pObject->Draw();

			// 次のオブジェクトを代入
			pObject = pObNext;
		}
	}

	// カメラの取得
	CCamera* pCamera = CManager::GetCamera();

	// カメラの設定
	pCamera->SetCamera();
}

//====================================================
// オブジェクトの死亡フラグを立てる
//====================================================
void CObject::Release(void)
{
	// 自身の死亡フラグを立てる
	this->m_bDeath = true;
}

//====================================================
// 死亡フラグが立ったオブジェクトの破棄
//====================================================
void CObject::Delete(int nPriority)
{
	CObject* pObject = m_pTop[nPriority];

	while (pObject != NULL)
	{
		// 次のポインタを保存
		CObject* pObNext = pObject->m_pNext;

		if (pObject->m_bDeath == true)
		{
			// 自身が先頭でも最後尾でもないなら
			if (m_pCur[nPriority] != pObject && m_pTop[nPriority] != pObject)
			{
				// 自身の仮保存
				CObject* pObjectKeep = pObject;

				// 自身の前のポインタの次のポインタを自身の次のポインタに設定
				pObject->m_pPrev->m_pNext = pObjectKeep->m_pNext;

				// 自身の次のポインタの前のポインタを自身の前のポインタに設定
				pObject->m_pNext->m_pPrev = pObjectKeep->m_pPrev;
			}

			// 先頭が自身なら
			if (m_pTop[nPriority] == pObject)
			{
				// 次のポインタが存在するなら
				if (pObNext != nullptr)
				{
					// 自身の次のポインタを先頭のポインタにする
					m_pTop[nPriority] = pObject->m_pNext;

					// 先頭のポインタの前のポインタをリストから消す
					m_pTop[nPriority]->m_pPrev = { nullptr };
				}

				// 自身のみなら
				else
				{
					// 先頭のポインタの前のポインタをリストから消す
					m_pTop[nPriority]->m_pPrev = { nullptr };

					// 先頭のポインタを空にする
					m_pTop[nPriority] = { nullptr };
					delete m_pTop[nPriority];

					// 最後尾を空にする
					m_pCur[nPriority] = { nullptr };
					delete m_pCur[nPriority];
				}
			}

			// 最後尾が自身なら
			if (m_pCur[nPriority] == pObject)
			{
				// 前のポインタが存在するなら
				if (pObject->m_pPrev != nullptr)
				{
					// 自身の前のポインタを最後尾のポインタにする
					m_pCur[nPriority] = pObject->m_pPrev;

					// 最後尾のポインタの次のポインタをリストから消す
					m_pCur[nPriority]->m_pNext = { nullptr };
				}
				else
				{ 
					// 最後尾を空にする
					m_pCur[nPriority] = { nullptr };
					delete m_pCur[nPriority];
				}
			}

			// メモリの開放(自身の破棄)
			delete pObject;
			pObject = nullptr;
		}

		// 次のオブジェクトを代入
		pObject = pObNext;
	}
}