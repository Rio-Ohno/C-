//====================================================
//
// ゲーム情報 [gameInfo.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "main.h"

// 名前空間
// ゲーム情報
namespace GameInfo	
{
	// フレーム
	constexpr int FREAM_EVENT = 3000;
	constexpr int FREAM_EVENT_LAST = 1500;

	// カメラ
	namespace Camera	
	{
		const D3DXVECTOR3 POS = { 0.0f, 175.0f, -300.0f };	// 視点
		const D3DXVECTOR3 TARGET = D3DXVECTOR3_NULL;		// 注視点
		const D3DXVECTOR3 ROT = { 2.3f, 0.0f, 0.0f };		// 角度
	}

	// 空(球体)
	namespace Sky	
	{
		const D3DXVECTOR3 POS = D3DXVECTOR3_NULL;	// 位置
		const D3DXVECTOR3 ROT = D3DXVECTOR3_NULL;	// 角度
		constexpr int DIVISION_X = 8;				// X軸分割数
		constexpr int DIVISION_Y = 8;				// Y軸分割数
		constexpr float RADIUS = 600.0f;			// 半径
		constexpr float ROT_SPEED = 0.0005f;		// 回転スピード
		constexpr bool IS_HALF_SPHERE = false;		// 半球かどうか
		constexpr bool FRONT_FACE = false;			// 表向きかどうか
	}

	// 壁
	namespace Wall	
	{
		typedef enum
		{
			TYPE_DISPLAY,	// 表示
			TYPE_FRONT,		// 前
			TYPE_BACK,		// 後ろ
			TYPE_LEFT,		// 左
			TYPE_RIGHT,		// 右
			TYPE_MAX
		}TYPE;				// 種類

		// 位置
		const D3DXVECTOR3 POS_DISPLAY = { 0.0f, -120.0f, -120.0f };
		const D3DXVECTOR3 POS_FRONT = { 0.0f, 0.0f, -120.0f };
		const D3DXVECTOR3 POS_BACK = { 0.0f, 0.0f, 120.0f };
		const D3DXVECTOR3 POS_LEFT = { 140.0f, 0.0f, 0.0f };
		const D3DXVECTOR3 POS_RIGHT = { -140.0f, 0.0f, 0.0f };

		// 角度
		const D3DXVECTOR3 ROT_DISPLAY = D3DXVECTOR3_NULL;
		const D3DXVECTOR3 ROT_FRONT = { 0.0f, D3DX_PI, 0.0f };
		const D3DXVECTOR3 ROT_BACK = { 0.0f, 0.0f, 0.0f };
		const D3DXVECTOR3 ROT_LEFT = { 0.0f, PI_HALF, 0.0f };
		const D3DXVECTOR3 ROT_RIGHT = { 0.0f, -PI_HALF, 0.0f };

		// 幅
		constexpr float WIDTH_DISPLAY = 280.0f;
		constexpr float WIDTH_FRONT = 280.0f;
		constexpr float WIDTH_BACK = 280.0f;
		constexpr float WIDTH_LEFT = 240.0f;
		constexpr float WIDTH_RIGHT = 240.0f;

		// 高さ
		constexpr float HEIGHT = 120.0f;

		// 表示するかどうか
		constexpr bool DISPLAY_DISPLAY = true;
		constexpr bool DISPLAY_OTHER = false;

		// 当たり判定をとるかどうか
		constexpr bool IS_COLLISION_DISPLAY = false;
		constexpr bool IS_COLLISION_OTHER = true;
	}

	// フィールド
	namespace Filed	
	{
		const D3DXVECTOR3 POS = D3DXVECTOR3_NULL;	// 位置
		const D3DXVECTOR3 ROT = D3DXVECTOR3_NULL;	// 角度

		constexpr int DIVISION_X = 40;				// X軸分割数
		constexpr int DIVISION_Z = 40;				// Z軸分割数
		constexpr int WIDTH = 7;					// 幅
		constexpr int HEIGHT = 6;					// 高さ
	}

	// ゲットホール
	namespace Hole	
	{
		const D3DXVECTOR3 POS = { 95.0f, 0.0f, 70.0f };	// 位置
		const D3DXVECTOR3 ROT = { 0.0f, PI_HALF, 0.0f };// 角度

		constexpr int DIVISION_X = 16;					// X軸分割数
		constexpr int DIVISION_Y = 1;					// Y軸分割数
		constexpr float RADIUS = 40.0f;					// 半径
		constexpr float HIGHT = 10.0f;					// 高さ
	}

	// プレイヤー
	namespace Player	
	{
		const D3DXVECTOR3 POS = { 95.0f, 65.0f, 70.0f };// 位置
		const D3DXVECTOR3 ROT = D3DXVECTOR3_NULL;		// 角度
	}

	// タイムマネージャー
	namespace TimeManager	
	{
		const D3DXVECTOR3 POS = { 740.0f, 60.0f, 0.0f };// 位置

		constexpr int FREAM = 5400;						// フレーム数
		constexpr int DIGIT = 3;						// 桁数
		constexpr float WIDTH = 40.0f;					// 幅
		constexpr float HEIGHT = 60.0f;					// 高さ
	}

	// スコア
	namespace Score	
	{
		const D3DXVECTOR3 POS = { 360.0f, 60.0f, 0.0f };	// 位置

		constexpr int DIGIT = 6;							// 桁数
		constexpr float WIDTH = 45.0f;						// 幅
		constexpr float HEIGHT = 65.0f;						// 高さ
	}
}