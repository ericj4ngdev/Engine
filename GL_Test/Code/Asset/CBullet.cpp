#include "include.h"

CBullet::CBullet()
{
	Init();
}

CBullet::CBullet(string name) : CGameObject(name)
{
	Init();
}

CBullet::~CBullet() = default;

void CBullet::Init()
{
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\weapon.png";
	CreateComponent<CCollider>();
	CreateComponent<Bullet>();
	CreateComponent<CAnimator>();
	SetScale(vec2(16, 12));
	GetComponent<CAnimator>()->SetTexture("BulletTex", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();
	
	GetComponent<CAnimator>()->CreateAnimation("Bullet", pTex, vec2(220, 10), vec2(8, 6), vec2(0, 0), 1, 0.5f, 1);
	// GetComponent<CAnimator>()->CreateAnimation("Bullet", pTex, vec2(347, 66), vec2(34, 24), vec2(0, 0), 1, 0.5f, 1);
}

void CBullet::Update()
{
	CGameObject::Update();
	vec2 vRenderPos = GetComponent<CAnimator>()->GetAnimation()->GetRenderPos();
	// printf("vRenderPos.x : %f\n", vRenderPos.x);
	if (vRenderPos.x <= -1 || vRenderPos.x >= GLMgr::g_screenWidth)
	{
		DeleteObject(this);
		printf("CBullet::Update() -> Deleted\n");
	}
}


void CBullet::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (dynamic_cast<CEnemy*>(pOtherObj))
	{
		DeleteObject(pOtherObj);
		DeleteObject(this);
	}
}
