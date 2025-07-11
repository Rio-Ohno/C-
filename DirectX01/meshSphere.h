//============================================================
//
//メッシュスフィア[meshSphere.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

// インクルード
#include "main.h"
#include"object.h"
																												   
//球の構造体																									 　 
typedef struct																									   
{																												   
	D3DXVECTOR3 pos;																							// 位置
	D3DXVECTOR3 rot;																							// 向き
	D3DXCOLOR col;																								// 色
	D3DXMATRIX mtxWorld;																						// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;																			// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIndxBuff;																			// インデクスバッファへのポインタ
	int textype;																								// テクスチャの種類
	int DiviX;																									// 分割数
	int DiviY;																									// 分割数
	int nMaxVtx;																								// 頂点数 
	int nPolyNum;																								// ポリゴン数
	float  fRadius;																								// 半径
	bool bHalf;																									// 半球かどうか
	bool bHead;																									// 表かどうか
	bool bUse;																									// 使用しているかどうか
}MeshSphere;																									   
																												   
//プロトタイプ宣言																								   
void InitSphere(void);																							// 初期化処理
void UninitSphere(void);																						// 終了処理
void UpdateSphere(void);																						// 更新処理
void DrawSphere(void);																							// 描画処理
int SetSphere(D3DXVECTOR3 pos, int textype, int DiviX, int DiviY, float fRadius, bool bHead, bool bHalf);		// 設定処理
void SetSpherePos(int indx,D3DXVECTOR3 pos);																	// 位置の設定処理
void SetSphereTexture(int indx);																				// テクスチャの設定処理
//void DeleteSphere(int indx);																					// 消す処理

class CMeshSphere :public CObject
{
public:
	CMeshSphere();
	~CMeshSphere();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetColor(D3DXCOLOR col);
	void BindTexIndex(int indx);

	D3DXVECTOR3 GetPos(void);

	static CMeshSphere* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDiviX, int nDiviY, float fRadius, bool bHalf);

private:
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_rot;								// 向き
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIndxBuff;				// インデクスバッファへのポインタ
	int m_nTexindx;									// テクスチャインデックス
	int m_nDiviX;									// 分割数
	int m_nDiviY;									// 分割数
	int m_nMaxVtx;									// 頂点数 
	int m_nPolyNum;									// ポリゴン数
	float  m_fRadius;								// 半径
	bool m_bHalf;									// 半球かどうか
	bool m_bFront;									// 表向きかどうか
};
#endif // !_MESHSPHERE_H_
