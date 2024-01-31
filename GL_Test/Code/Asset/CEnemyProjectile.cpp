#include "include.h"

CEnemyProjectile::CEnemyProjectile() : m_fSpeed(0)
	, m_vDir(vec2(0,0))
{
	Init();
}

CEnemyProjectile::CEnemyProjectile(string name) : m_fSpeed(0)
, m_vDir(vec2(0, 0))
{
	Init();
}

CEnemyProjectile::~CEnemyProjectile() = default;

void CEnemyProjectile::Init()
{
	CreateComponent<CAnimator>();
	CreateComponent<CCollider>();
	// SetScale();
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\NES - Mega Man 2 - Enemies.png";
	GetComponent<CAnimator>()->SetTexture("EnemyProjectile", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();
	GetComponent<CAnimator>()->CreateAnimation("Carrot", pTex, vec2(109, 587), vec2(14, 14), vec2(0, 0), 1, 0.5f, 1);
	SetScale(vec2(50, 50));
	GetComponent<CCollider>()->Init();
	// 123, 571
}

void CEnemyProjectile::Update()
{
	CGameObject::Update();
	GetComponent<CAnimator>()->Play("Carrot", true);
	ScreenOut();
	Movement();
	// 
}

void CEnemyProjectile::OnCollisionEnter(CCollider* pOther)
{
	// printf("CEnemyProjectile\n");

}



void CEnemyProjectile::Movement()
{
	// m_vDir은 외부에서 정한다.
	vec2 pos = m_transform->GetPosition();
	pos += m_vDir * m_fSpeed * fDT;
	m_transform->SetPosition(pos);
}

void CEnemyProjectile::ScreenOut()
{
	vec2 vRenderPos = GetComponent<CAnimator>()->GetAnimation()->GetRenderPos();
	// printf("vRenderPos.x : %f\n", vRenderPos.x);
	if (vRenderPos.x <= -1 || vRenderPos.x >= GLMgr::g_screenWidth)
	{
		DeleteObject(this);
		
	}
}
