//====================================================
//
// タイトル情報 [titleInfo.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "main.h"

// 名前空間
// タイトル情報
namespace TitleInfo
{
	// カメラ
	namespace Camera
	{
		const D3DXVECTOR3 POS = { 0.0f, 340.0f, 0.0f };		// 視点
		const D3DXVECTOR3 TARGET = { 0.0f, 50.0f, 0.0f };	// 注視点
		const D3DXVECTOR3 ROT = { 1.6f, 0.0f, 0.0f };		// 向き
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
		// 位置
		const D3DXVECTOR3 POS_FRONT = { 0.0f, -120.0f, 120.0f };
		const D3DXVECTOR3 POS_BACK = { 0.0f, -120.0f, -120.0f };
		const D3DXVECTOR3 POS_LEFT = { 140.0f, -120.0f, 0.0f };
		const D3DXVECTOR3 POS_RIGHT = { -140.0f, -120.0f, 0.0f };

		// 角度
		const D3DXVECTOR3 ROT_FRONT = { 0.0f, D3DX_PI, 0.0f };
		const D3DXVECTOR3 ROT_BACK = { 0.0f, 0.0f, 0.0f };
		const D3DXVECTOR3 ROT_LEFT = { 0.0f, -PI_HALF, 0.0f };
		const D3DXVECTOR3 ROT_RIGHT = { 0.0f, PI_HALF, 0.0f };

		// 幅
		constexpr float WIDTH_FRONT = 280.0f;
		constexpr float WIDTH_BACK = 280.0f;
		constexpr float WIDTH_LEFT = 240.0f;
		constexpr float WIDTH_RIGHT = 240.0f;

		// 高さ
		constexpr float HEIGHT = 120.0f;

		// 当たり判定をとるかどうか
		constexpr bool IS_COLLISION = false;

		// 表示するかどうか
		constexpr bool IS_DISPLAY = true;
	}

	// フィールド
	namespace Field
	{
		const D3DXVECTOR3 POS = D3DXVECTOR3_NULL;	// 位置
		const D3DXVECTOR3 ROT = D3DXVECTOR3_NULL;	// 角度

		constexpr int DIVISION_X = 40;				// X軸分割数
		constexpr int DIVISION_Z = 40;				// Z軸分割数
		constexpr int WIDTH = 7;					// 幅
		constexpr int HEIGHT = 6;					// 高さ
	}

	// プレイヤー
	namespace Player
	{
		const D3DXVECTOR3 POS = { 95.0f, 85.0f, 70.0f };// 位置
		const D3DXVECTOR3 ROT = D3DXVECTOR3_NULL;		// 角度
	}

	// UI
	namespace UI
	{
		namespace POP
		{
			const D3DXVECTOR3 POS = { 640.0f, 75.0f, 0.0f };// 位置
			constexpr float WIDTH = 1280.0f;// 幅
			constexpr float HEIGHT = 150.0f;// 高さ
		}

		namespace TITLE
		{
			const D3DXVECTOR3 POS = { 640.0f, 80.0f, 0.0f };// 位置
			constexpr float WIDTH = 550.0f;	// 幅
			constexpr float HEIGHT = 175.0f;// 高さ
		}

		namespace ENTER
		{
			const D3DXVECTOR3 POS = { 640.0f, 600.0f, 0.0f };// 位置
			constexpr float WIDTH = 600.0f;	// 幅
			constexpr float HEIGHT = 120.0f;// 高さ
		}
	}
}