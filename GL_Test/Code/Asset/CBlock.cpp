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
	CreateComponent<CRenderComponent>();
	CreateComponent<CCollider>();
	GetComponent<CRenderComponent>()->SetTexture("Block", strFilePath.c_str());
	

}

void CBlock::OnCollisionEnter(CCollider* pOther)
{
	printf("Collide with %s\n", pOther->gameObject->GetName().c_str());
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player") 
	{
		// 땅에 안착했음을 알려줌
		// pOtherObj->GetComponent<CRigidbody>()->GetGround(true);

		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// 플레이어가 땅을 파고 든 길이 = (높이 합 / 2) - (중심점 사이 y 거리)
		float fLen = abs(vObjPos.y - vPos.y); 
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - abs(vObjPos.y - vPos.y);

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		vObjPos.y += (fPush - 1);

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player")
	{
		// 땅에 안착했음을 알려줌
		// pOtherObj->GetComponent<CRigidbody>()->GetGround(true);

		// 플레이어
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// 땅
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// 플레이어가 땅을 파고 든 길이 = (높이 합 / 2) - (중심점 사이 y 거리)
		float fLen = abs(vObjPos.y - vPos.y);
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - abs(vObjPos.y - vPos.y);

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		vObjPos.y += (fPush - 1);

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player")
	{
		// 땅에 안착했음을 알려줌
		// pOtherObj->GetComponent<CRigidbody>()->GetGround(false);

	}
}
