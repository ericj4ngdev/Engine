#include "include.h"


CEnemy::CEnemy(string name) : CGameObject(name), m_curpos(vec2(0,0))
{
	Init();
}

CEnemy::~CEnemy() = default;

void CEnemy::Init()
{
	CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	CreateComponent<CCollider>();
	CreateComponent<CAnimator>();

	GetComponent<CRigidbody>()->SetFriction(700.0f);
	GetComponent<CRigidbody>()->SetMaxVelocity(vec2(100.0f, 1000.0f));
	GetComponent<CGravity>()->SetGravity(1700.0f);

	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\Enemy.png";
	GetComponent<CAnimator>()->SetTexture("Zombie1Tex", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();

	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Idle_Left", pTex, vec2(124, 611), vec2(32, 38), vec2(0, 0), 1, 0.5f, 1);
	// 156 574
	m_fSpeed = 100;
}

void CEnemy::Update()
{
	CGameObject::Update();
	// m_curpos.x = m_transform->GetPosition().x;
	// m_curpos.x -= m_fSpeed * fDT;
	// SetPos(m_curpos);
	GetComponent<CAnimator>()->Play("Rabbit_Idle_Left", true);
	// printf("Enemy (%f, %f)\n", m_curpos.x, m_curpos.y);
}



void CEnemy::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (dynamic_cast<CBullet*>(pOtherObj))
	{
		DeleteObject(this);
	}
}
