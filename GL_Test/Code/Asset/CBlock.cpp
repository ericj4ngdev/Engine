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
		// ���� ���������� �˷���
		// pOtherObj->GetComponent<CRigidbody>()->GetGround(true);

		// �÷��̾�
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// ��
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// �÷��̾ ���� �İ� �� ���� = (���� �� / 2) - (�߽��� ���� y �Ÿ�)
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
		// ���� ���������� �˷���
		// pOtherObj->GetComponent<CRigidbody>()->GetGround(true);

		// �÷��̾�
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// ��
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// �÷��̾ ���� �İ� �� ���� = (���� �� / 2) - (�߽��� ���� y �Ÿ�)
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
		// ���� ���������� �˷���
		// pOtherObj->GetComponent<CRigidbody>()->GetGround(false);

	}
}
