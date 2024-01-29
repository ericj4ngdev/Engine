#include "include.h"

CBlock::CBlock(string name) : CGameObject(name)
{
	Init();
}

CBlock::~CBlock() = default;

void CBlock::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\block.png";
	// CreateComponent<CRenderComponent>();
	CreateComponent<CCollider>();
	// GetComponent<CRenderComponent>()->SetTexture("Block", strFilePath.c_str());
	

}

void CBlock::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player") 
	{
		// 땅에 안착했음을 알려줌
		// 이미 true이면 패스
		if (pOtherObj->GetComponent<CGravity>()->GetGround()) return;
		pOtherObj->GetComponent<CGravity>()->SetGround(true);

		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// 플레이어가 땅을 파고 든 길이 = (높이 합 / 2) - (중심점 사이 y 거리)
		float fLen = abs(vObjPos.y - vPos.y); 
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		// assert(count == 0);
		if (count == 0) return;
		vObjPos.y += (float)(fPush / count);

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
	else if (dynamic_cast<CEnemy*>(pOtherObj))
	{
		// col++;
		// 땅에 안착했음을 알려줌
		// if (pOtherObj->GetComponent<CGravity>()->GetGround()) return;
		pOtherObj->GetComponent<CGravity>()->SetGround(true);// 안착 시 중력 X


		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// 플레이어가 땅을 파고 든 길이 = (높이 합 / 2) - (중심점 사이 y 거리)
		float fLen = abs(vObjPos.y - vPos.y);
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		vObjPos.y += (float)(fPush);

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player")
	{
		// col++;
		// 땅에 안착했음을 알려줌
		// if (pOtherObj->GetComponent<CGravity>()->GetGround()) return;
		pOtherObj->GetComponent<CGravity>()->SetGround(true);// 안착 시 중력 X
		

		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// 플레이어가 땅을 파고 든 길이 = (높이 합 / 2) - (중심점 사이 y 거리)
		float fLen = abs(vObjPos.y - vPos.y);
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		if (count == 0) return;
		vObjPos.y += (float)(fPush / count);	// 더 밀어버려. position을 더 파먹게. 더 적게 더한다.

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
	else if (dynamic_cast<CEnemy*>(pOtherObj))
	{
		static_cast<CEnemy*>(pOtherObj)->GetComponent<CGravity>()->SetGround(true);// 안착 시 중력 X

		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		vObjPos.y += (float)(fPush);	

		static_cast<CEnemy*>(pOtherObj)->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player")
	{
		// 땅에 안착했음을 알려줌
		pOtherObj->GetComponent<CGravity>()->SetGround(false);
	}
}
