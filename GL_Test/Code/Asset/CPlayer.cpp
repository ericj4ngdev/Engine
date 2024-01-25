#include "include.h"

CPlayer::CPlayer(string name) : CGameObject(name)
{
	Init();
}

CPlayer::~CPlayer() = default;

void CPlayer::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	// strFilePath += "texture\\player.png";
	// CreateComponent<CRenderComponent>();
	CreateComponent<ControllerComponent>();
	CreateComponent<CCollider>();
	CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	
	GetComponent<ControllerComponent>()->SetSpeed(200.0f);
	// 조종에 AddForce를 안해서 무의미 
	GetComponent<CRigidbody>()->SetFriction(100.0f);		
	// x값 무의미
	GetComponent<CRigidbody>()->SetMaxVelocity(vec2(200.0f, 800.0f));
	GetComponent<CGravity>()->SetGravity(1000);

	
	CreateComponent<CAnimator>();
	strFilePath += "texture\\castlevania3.png";
	GetComponent<CAnimator>()->SetTexture("PlayerTex", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();

	GetComponent<CAnimator>()->CreateAnimation("Walk", pTex, vec2(8, 146), vec2(16,32), vec2(40,0), 0.5f, 4);
	// GetComponent<CAnimator>()->CreateAnimation("Walk", pTex, vec2(1,1), vec2(1,1), vec2(0, 0), 0.1f, 3);
	GetComponent<CAnimator>()->Play("Walk", true);

	CAnimation* pAnim = GetComponent<CAnimator>()->FindAnimation("Walk");
	for (int i = 0; i < pAnim->GetMaxFrame(); i++) 
	{
		pAnim->GetFrame(i).vOffset = vec2(0, 0.f);
	}

	m_StepedBlockCount = 0;
}

void CPlayer::OnCollisionEnter(CCollider* pOther)
{
	// printf("Collide with %s, count : %d\n", pOther->gameObject->GetName().c_str(), c);
	CGameObject* pOtherObj = pOther->gameObject;
	// 블럭이면
	if(dynamic_cast<CBlock*>(pOtherObj)) 
	{
		m_StepedBlockCount++;
		static_cast<CBlock*>(pOtherObj)->SetCount(m_StepedBlockCount);		
	}
}

void CPlayer::OnCollision(CCollider* pOther)
{
	printf("CPlayer::OnCollision -> count : %d\n", m_StepedBlockCount);
}


void CPlayer::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	// 블럭이면
	if (dynamic_cast<CBlock*>(pOtherObj))
	{
		m_StepedBlockCount--;
		static_cast<CBlock*>(pOtherObj)->SetCount(m_StepedBlockCount);
		// printf("count : %d\n", c);
	}
}
