//====================================================
//
// モデル(階層構造前提)[model.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _MODEL_H_
#define _MODEL_H_

// インクルード
#include "main.h"
#include <vector>

// モデルクラス
class CModel
{
public:
	CModel();
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);
	void Uninit(void);
	void Draw(void);

	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

	// セッター
	void SetParent(CModel* pModel);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetColor(D3DXCOLOR col) { m_col = col; };
	void ColorReset(void) { m_col = {}; };

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	LPD3DXMESH GetMesh(void) { return m_pMesh; };
	LPD3DXBUFFER GetBuffMat(void) { return m_pBuffMat; };
	DWORD GetdwNumMat(void) { return m_dwNumMat; };
	D3DXMATRIX GetMtxWorld(void);
private:
	LPD3DXMESH m_pMesh;			// メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアルへのポインタ
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	DWORD m_dwNumMat;			// マテリアルの数
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXCOLOR m_col;			// 色
	CModel* m_pParent;			// 親モデルへのポインタ

	static std::vector<int> m_nTexIndx;// テクスチャインデックス保存
	int m_nNumTex;
};

#endif // !_MODEL_H_
