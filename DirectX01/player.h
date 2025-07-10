//====================================================
//
// プレイヤー[player.h]
// Author:Rio Ohno
//
//====================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルード
#include"main.h"
#include"object.h"
#include"model.h"
#include"shadow.h"
#include"motion.h"

// マクロ定義
#define ANIME_SPAN (40)					// スプライトを切り替える感覚(フレーム)
#define PLAYER_SPEED ((float)0.5f)
#define NUM_MODEL (15)
#define MOTIONFILE_PLAYER ((const char*)"data/MODEL/player/motion.txt")

//プレイヤークラス
class CPlayer:public CObject
{
public:

	typedef enum
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_INVINCIBLE,
		STATE_MAX
	}State;

	//CPlayer();
	CPlayer(int nPriority = 3);
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//void SetState(State state);
	//State GetState(void);

	void Action(void);

	static HRESULT Load(void);
	static void UnLoad(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetMotion(const char* pFileName);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	float GetWidth(void) { return 0.0f; };
	float GetHeight(void) { return 0.0f; };
	D3DXVECTOR3 GetSize(void) { return m_size; };

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	static CMotion* m_pMotion;				// モーションへのポインタ
	static CLoadMotion* m_pLoadMotion;
	//static int m_nIndxTex;				// テクスチャへのインデックス
	D3DXVECTOR3 m_move;						// 移動量
	State m_state;							// 状態
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_posOld;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_DestRot;					// 向きの目標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXVECTOR3 m_vtxMax;					// 最大の頂点位置
	D3DXVECTOR3 m_vtxMin;					// 最小の頂点位置
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	CShadow* m_pShadow;						// 影へのポインタ
	int nNumModel;							// モデルの総数
	float m_fSpeed;

};

#endif // !_PLAYER_H_
