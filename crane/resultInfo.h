//====================================================
//
// リザルト情報 [resultInfo.h]
// Author:Rio Ohno
//
//====================================================

// インクルード
#include "main.h"

// 名前空間
// リザルト情報
namespace ResultInfo
{
	// UI
	namespace UI
	{
		// POPポリゴン
		namespace POP
		{
			const D3DXVECTOR3 POS = { 640.0f, 75.0f, 0.0f };
			constexpr float WIDTH = 1280.0f;
			constexpr float HEIGHT = 150.0f;
		}

		// Resultポリゴン
		namespace RESULT
		{
			const D3DXVECTOR3 POS = { 640.0f, 60.0f, 0.0f };
			constexpr float WIDTH = 600.0f;
			constexpr float HEIGHT = 120.0f;
		}
	}
}