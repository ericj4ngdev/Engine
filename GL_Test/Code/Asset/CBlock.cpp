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
	// printf("Collide with %s\n", pOther->gameObject->GetName().c_str());
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player") 
	{
		// ���� ���������� �˷���
		pOtherObj->GetComponent<CGravity>()->SetGround(true);

		// �÷��̾�
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// ��
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// �÷��̾ ���� �İ� �� ���� = (���� �� / 2) - (�߽��� ���� y �Ÿ�)
		float fLen = abs(vObjPos.y - vPos.y); 
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		// assert(count == 0);
		if (count == 0) return;
		vObjPos.y += (float)((fPush - 0.01f) / count);

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	// bool isGround = pOtherObj->GetComponent<CGravity>()->GetGround(true);
	// if(isGround)
	// int col = 0;
	if (pOtherObj->GetName() == "Player")
	{
		// col++;
		// ���� ���������� �˷���
		pOtherObj->GetComponent<CGravity>()->SetGround(true);

		// �÷��̾�
		vec2 vObjPos = pOther->GetPos();
		vec2 vObjScale = pOther->GetScale();

		// ��
		vec2 vPos = GetComponent<CCollider>()->GetPos();
		vec2 vScale = GetComponent<CCollider>()->GetScale();

		// �÷��̾ ���� �İ� �� ���� = (���� �� / 2) - (�߽��� ���� y �Ÿ�)
		float fLen = abs(vObjPos.y - vPos.y);
		float fPush = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetComponent<TransformComponent>()->GetPosition();
		if (count == 0) return;
		vObjPos.y += (float)((fPush - 0.01f) / count);	// �� �о����.

		pOtherObj->GetComponent<TransformComponent>()->SetPosition(vObjPos);
	}
}

void CBlock::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (pOtherObj->GetName() == "Player")
	{
		// ���� ���������� �˷���
		pOtherObj->GetComponent<CGravity>()->SetGround(false);
	}
}
