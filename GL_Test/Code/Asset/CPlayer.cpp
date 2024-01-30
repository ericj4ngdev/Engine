#include "include.h"

CPlayer::CPlayer(string name) : CGameObject(name)
{
	Init();
}

CPlayer::~CPlayer() = default;

void CPlayer::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	CreateComponent<CAnimator>();
	CreateComponent<ControllerComponent>();
	CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	CreateComponent<CCollider>();
	
	// 조종에 AddForce를 안해서 무의미 
	 GetComponent<CRigidbody>()->SetFriction(700.0f);		
	// x값 무의미
	GetComponent<CRigidbody>()->SetMaxVelocity(vec2(200.0f, 1000.0f));
	GetComponent<CGravity>()->SetGravity(1700.0f);

	
	
	strFilePath += "texture\\Rockman.png";
	GetComponent<CAnimator>()->SetTexture("PlayerTex", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();


	GetComponent<CAnimator>()->CreateAnimation("Idle_Right", pTex, vec2(101, 34), vec2(24, 24), vec2(30, 0), 1, 0.5f, 2);
	GetComponent<CAnimator>()->CreateAnimation("Walk_Right", pTex, vec2(188, 34), vec2(24, 24), vec2(28,0), 1, 0.15f, 4);
	GetComponent<CAnimator>()->CreateAnimation("Jump_Right", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), 1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Fall_Right", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), 1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Attack_Right", pTex, vec2(14, 70), vec2(32, 24), vec2(0, 0), 1, 0.1f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Run_Attack_Right", pTex, vec2(47, 70), vec2(32, 24), vec2(33, 0), 1, 0.15f, 3);
	GetComponent<CAnimator>()->CreateAnimation("Jump_Attack_Right", pTex, vec2(146, 70), vec2(26, 29), vec2(33, 0), 1, 0.15f, 1);

	GetComponent<CAnimator>()->CreateAnimation("Idle_Left", pTex, vec2(101, 34), vec2(24, 24), vec2(30, 0), -1, 0.5f, 2);
	GetComponent<CAnimator>()->CreateAnimation("Walk_Left", pTex, vec2(188, 34), vec2(24, 24), vec2(28, 0), -1, 0.15f, 4);
	GetComponent<CAnimator>()->CreateAnimation("Jump_Left", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), -1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Fall_Left", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), -1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Attack_Left", pTex, vec2(14, 70), vec2(32, 24), vec2(0, 0), -1, 0.1f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Run_Attack_Left", pTex, vec2(47, 70), vec2(32, 24), vec2(33, 0), -1, 0.15f, 3);
	GetComponent<CAnimator>()->CreateAnimation("Jump_Attack_Left", pTex, vec2(146, 70), vec2(26, 29), vec2(33, 0), -1, 0.15f, 1);

	// CAnimation* pAnim = GetComponent<CAnimator>()->FindAnimation("Attack_Right");
	// pAnim->GetFrame(2).vOffset = vec2(0, -10.f);
	// pAnim->GetFrame(2).vSlice = vec2(48, 32);
	// pAnim->GetFrame(2).fD = 0.3f;
	// pAnim = GetComponent<CAnimator>()->FindAnimation("Sit_Right");
	// pAnim->GetFrame(0).vOffset = vec2(0, -10.f);
	// pAnim = GetComponent<CAnimator>()->FindAnimation("Jump_Right");
	// pAnim->GetFrame(0).vOffset = vec2(0, -10.f);
	// pAnim = GetComponent<CAnimator>()->FindAnimation("Jump_Left");
	// pAnim->GetFrame(0).vOffset = vec2(0, -10.f);


	/*CAnimation* pAnim = GetComponent<CAnimator>()->FindAnimation("Jump_Left");
	for (int i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = vec2(0, -1000.f);

	pAnim = GetComponent<CAnimator>()->FindAnimation("Jump_Right");
	for (int i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = vec2(0, -1000.f);*/

	


	GetComponent<ControllerComponent>()->SetSpeed(200.0f);
	m_StepedBlockCount = 0;
}

void CPlayer::Update()
{
	CGameObject::Update();
}

void CPlayer::OnCollisionEnter(CCollider* pOther)
{
	// printf("Collide with %s, count : %d\n", pOther->gameObject->GetName().c_str(), c);
	CGameObject* pOtherObj = pOther->gameObject;
	// 블럭이면
	if(dynamic_cast<CBlock*>(pOtherObj)) 
	{
		vec2 vPos = GetPos();
		vec2 vScale = GetScale();
		m_StepedBlockCount++;
		static_cast<CBlock*>(pOtherObj)->SetCount(m_StepedBlockCount);	

	}
}

void CPlayer::OnCollision(CCollider* pOther)
{
	// printf("CPlayer::OnCollision -> count : %d\n", m_StepedBlockCount);
}


void CPlayer::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	// 블럭이면
	if (dynamic_cast<CBlock*>(pOtherObj))
	{
		m_StepedBlockCount--;
		static_cast<CBlock*>(pOtherObj)->SetCount(m_StepedBlockCount);
		// printf("count : %d\n", m_StepedBlockCount);
	}
}
