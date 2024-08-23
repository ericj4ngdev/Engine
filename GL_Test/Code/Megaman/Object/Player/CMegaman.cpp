#include "include.h"

CMegaman::CMegaman(string name) : CCharacter(name)
	, m_iDir(1)
	, m_bInvincible(false)
	, m_bInvincibleTimer(0)
	, m_StepedBlockCount(0)
{
	m_Animator = CreateComponent<CAnimator>();
	m_Rigidbody = CreateComponent<CRigidbody>();
	m_Gravity = CreateComponent<CGravity>();
	m_Collider = CreateComponent<CCollider>();
}

CMegaman::~CMegaman() = default;

void CMegaman::Init()
{
	// 조종에 AddForce를 안해서 무의미 
	m_Rigidbody->SetFriction(700.0f);
	// x값 무의미
	m_Rigidbody->SetMaxVelocity(vec2(200.0f, 1000.0f));
	m_Gravity->SetGravity(1700.0f);
		
	InitAnimation();
	
	// GetComponent<ControllerComponent>()->SetSpeed(200.0f);	
	CCharacter::Init();
}

void CMegaman::Update()
{
	CCharacter::Update();	
	m_curpos = GetPos();
	LOG("m_curPos : %d %d", m_curpos.x, m_curpos.y)
	if (m_bInvincible)
	{
		m_bInvincibleTimer += fDT;
		if (m_bInvincibleTimer < 2)
		{
			m_Animator->SetAlpha(0.5);
		}
		else
		{
			m_Animator->SetAlpha(1);
			m_bInvincible = false;
			m_bInvincibleTimer = 0;
		}
	}

	float move = 0;

	bool moveLeft = GetKeyHold(LEFT);
	bool moveRight = GetKeyHold(RIGHT);

	if (moveLeft || moveRight) 
	{
		if (moveLeft) { m_iDir = -1; }
		else { m_iDir = 1; }

		move = m_iDir * m_speed;
		m_curpos.x += move * fDT;
	}
	SetPos(m_curpos);
}

void CMegaman::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	// 블럭이면
	if (dynamic_cast<CBlock*>(pOtherObj))
	{
		vec2 vPos = GetPos();
		vec2 vScale = GetScale();
		m_StepedBlockCount++;
		static_cast<CBlock*>(pOtherObj)->SetCount(m_StepedBlockCount);
	}
}

void CMegaman::OnCollision(CCollider* pOther)
{
}

void CMegaman::OnCollisionExit(CCollider* pOther)
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

void CMegaman::Jump()
{
	CCharacter::Jump();
}

void CMegaman::InitAnimation()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\Rockman.png";
	m_Animator->SetTexture("PlayerTex", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();
	m_Animator->CreateAnimation("Idle_Right", pTex, vec2(101, 34), vec2(24, 24), vec2(30, 0), 1, 0.5f, 2);
	m_Animator->CreateAnimation("Walk_Right", pTex, vec2(188, 34), vec2(24, 24), vec2(28, 0), 1, 0.15f, 4);
	m_Animator->CreateAnimation("Jump_Right", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), 1, 0.5f, 1);
	m_Animator->CreateAnimation("Fall_Right", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), 1, 0.5f, 1);
	m_Animator->CreateAnimation("Attack_Right", pTex, vec2(14, 70), vec2(32, 24), vec2(0, 0), 1, 0.1f, 1);
	m_Animator->CreateAnimation("Run_Attack_Right", pTex, vec2(47, 70), vec2(32, 24), vec2(33, 0), 1, 0.15f, 3);
	m_Animator->CreateAnimation("Jump_Attack_Right", pTex, vec2(146, 70), vec2(26, 29), vec2(33, 0), 1, 0.15f, 1);

	m_Animator->CreateAnimation("Idle_Left", pTex, vec2(101, 34), vec2(24, 24), vec2(30, 0), -1, 0.5f, 2);
	m_Animator->CreateAnimation("Walk_Left", pTex, vec2(188, 34), vec2(24, 24), vec2(28, 0), -1, 0.15f, 4);
	m_Animator->CreateAnimation("Jump_Left", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), -1, 0.5f, 1);
	m_Animator->CreateAnimation("Fall_Left", pTex, vec2(296, 34), vec2(26, 29), vec2(0, 0), -1, 0.5f, 1);
	m_Animator->CreateAnimation("Attack_Left", pTex, vec2(14, 70), vec2(32, 24), vec2(0, 0), -1, 0.1f, 1);
	m_Animator->CreateAnimation("Run_Attack_Left", pTex, vec2(47, 70), vec2(32, 24), vec2(33, 0), -1, 0.15f, 3);
	m_Animator->CreateAnimation("Jump_Attack_Left", pTex, vec2(146, 70), vec2(26, 29), vec2(33, 0), -1, 0.15f, 1);

	m_Animator->CreateAnimation("Hit_Right", pTex, vec2(248, 70), vec2(26, 28), vec2(0, 0), 1, 0.15f, 1);
	m_Animator->CreateAnimation("Hit_Left", pTex, vec2(248, 70), vec2(26, 28), vec2(0, 0), -1, 0.15f, 1);
}

void CMegaman::TakeDamage(float damage, int dir)
{
	// GetComponent<ControllerComponent>()->TakeDamage(damage, dir);
}
