//====================================================
// 
//  “–‚½‚è”»’è [collision.cpp]
// AuthorFRio Ohno
// 
//====================================================

// ƒCƒ“ƒNƒ‹[ƒh
#include "collision.h"

//====================================================
// ‹…“¯m‚Ì“–‚½‚è”»’è
//====================================================
bool CCollision::CheckCollision(CColliderSphere* aSphere, CColliderSphere* bSphere)
{
	if (aSphere != nullptr && bSphere != nullptr)
	{
		D3DXVECTOR3 diff = aSphere->GetCenter() - bSphere->GetCenter();	// 2“_‚Ì·•ªZo
		float fDistSq = D3DXVec3LengthSq(&diff);						// ‹——£‚Ì—İæZo
		float fRadusSum = aSphere->GetRadius() + bSphere->GetRadius();	// ”¼Œa‡Z
		
		return fDistSq < (fRadusSum * fRadusSum);// ”äŠr
	}

	return false;
}

//====================================================
// ‹…‚Æ‰~’Œ‚Ì“àÚ”»’è(‰~’Œ‚³‚ê‚é•û)
//====================================================
bool CCollision::CheckEnterCollision(CColliderCylinder* pCylinder, CColliderSphere* pSphere)
{
	if (pCylinder != nullptr && pSphere != nullptr)
	{
		D3DXVECTOR3 diff = pSphere->GetCenter() - pCylinder->GetPos();		// 2“_‚Ì·•ªZo
		float fDistXSq = diff.x * diff.x;									// ‹——£‚Ì—İæZo(X²)
		float fDistZSq = diff.z * diff.z;									// ‹——£‚Ì—İæZo(Z²)
		float fRadusdiff = pCylinder->GetRadius() -pSphere->GetRadius();	// ”¼Œa‚Ì·‚ğZo

		// •½•ûª
		float fDistance = sqrtf(fDistXSq + fDistZSq);

		if (fDistance <= pCylinder->GetRadius() &&// ‰~‚Ì“–‚½‚è”»’è‚ª“–‚½‚Á‚Ä‚é‚©‚Â
			(pSphere->GetCenter().y + pSphere->GetRadius()) >= pCylinder->GetPos().y &&// ‚‚³‚ª‚ ‚Á‚Ä‚¢‚é‚È‚ç
			(pSphere->GetCenter().y - pSphere->GetRadius()) <= (pCylinder->GetPos().y + pCylinder->GetHeight()))
		{
			return true;
		}
	}

	return false;
}