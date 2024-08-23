#include "include.h"

CBat::CBat()
{
	m_fSpeed = 50;
	m_fMoveTimer = 0;
	m_bReady = true;
	m_bHit = false;
	m_pRigidbody = CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	m_pCollider = CreateComponent<CCollider>();
	// Init();
}

CBat::CBat(string name) : CEnemy(name)
{
	m_fSpeed = 80;
	m_fMoveTimer = 0;
	m_bReady = true;
	m_bHit = false;
	m_pRigidbody = CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	m_pCollider = CreateComponent<CCollider>();
	// Init();
}

CBat::~CBat()
{

}

void CBat::Init()
{
	m_pRigidbody->SetFriction(700.0f);
	m_pRigidbody->SetMaxVelocity(vec2(300.0f, 1000.0f));
	SetScale(vec2{ 75.f, 80.f });

	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\NES - Mega Man 2 - Enemies.png";
	m_Animator->SetTexture("Enemy", strFilePath.c_str());
	CTexture* pTex = m_Animator->GetTexture();

	m_Animator->CreateAnimation("Bat_Idle", pTex, vec2(1, 116), vec2(16, 24), vec2(0, 0), 1, 0.5f, 1);
	m_Animator->CreateAnimation("Bat_Ready", pTex, vec2(1, 141), vec2(32, 24), vec2(33, 0), 1, 0.1f, 4);
	m_Animator->CreateAnimation("Bat_Fly", pTex, vec2(133, 141), vec2(32, 24), vec2(33, 0), 1, 0.1f, 3);

	CEnemy::Init();
}

void CBat::Update()
{
	CGameObject::Update();
	
	m_fMoveTimer += fDT;
	if (m_fMoveTimer >= 2.0f && m_bReady)
	{
		m_bReady = false;
		ChangeState(ENEMY_STATE::READY);
	}
	if (m_fMoveTimer >= 2.2f && !m_bHit) Move();


	// 맞고 Idle 가면 m_fMoveTimer =0, m_bReady는 다시 true;
	if (m_bHit && m_eCurState != ENEMY_STATE::IDLE)
	{
		BackToIdle();
	}
	
	printf("State : %d\n", m_eCurState);

	UpdateState();

	ScreenOut();
}

void CBat::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;

	if (dynamic_cast<CPlayer*>(pOtherObj))
	{
		int dir = 0;

		dir = (pOtherObj->GetPos().x > GetPos().x) ? 1 : -1;
		// 플레이어에게 신호
		static_cast<CPlayer*>(pOtherObj)->TakeDamage(m_fDamage, dir);
		m_bHit = true;	
		
	}
}

void CBat::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;

	if (dynamic_cast<CPlayer*>(pOtherObj))
	{
		int dir = 0;

		dir = (pOtherObj->GetPos().x > GetPos().x) ? 1 : -1;
		// 플레이어에게 신호
		static_cast<CPlayer*>(pOtherObj)->TakeDamage(m_fDamage, dir);
		m_bHit = true;
	}
}


void CBat::TakeDamage()
{
	if (m_eCurState == ENEMY_STATE::IDLE) 
	{
		// 총알 튕기기

	}
	else
	{
		DeleteObject(this);
	}
}

void CBat::UpdateState()
{
	switch (m_eCurState)
	{
	case ENEMY_STATE::IDLE:
		m_Animator->Play("Bat_Idle", true);
		break;
	case ENEMY_STATE::READY:
		m_Animator->Play("Bat_Ready", false);
		break;
	case ENEMY_STATE::MOVE:
		m_Animator->Play("Bat_Fly", true);
		break;
	case ENEMY_STATE::JUMP:
		break;
	case ENEMY_STATE::FALL:
		break;
	case ENEMY_STATE::ATTACK:
		break;
	case ENEMY_STATE::HIT:
		m_Animator->Play("Bat_Fly", true);
		break;
	case ENEMY_STATE::DEAD:
		break;
	default:
		break;
	}
}

void CBat::Move()
{
	ChangeState(ENEMY_STATE::MOVE);
	vec2 playerPos = GetPlayerPosition();
	vec2 dir = (playerPos - GetPos()).Normalize();
	vec2 vCurPos = GetPos();
	vCurPos += dir * m_fSpeed * fDT;
	SetPos(vCurPos);
}

void CBat::Ready()
{
	
}

void CBat::BackToIdle()
{	
	vec2 vCurPos = GetPos();
	
	// 나무 높이로 올라가기
	if (vCurPos.y < 200) 
	{
		ChangeState(ENEMY_STATE::HIT);
		vCurPos.y += 500 * fDT;
		m_fMoveTimer = 0;
		m_bReady = true;
		SetPos(vCurPos);
	}
	else 
	{
		m_bHit = false;
		ChangeState(ENEMY_STATE::IDLE);
	}
}

