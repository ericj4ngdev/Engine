#include "include.h"

CRabbit::CRabbit()
{
	m_iDir = 1;
	m_attackCount = 0;
	m_fAttackTimer = 0;
	m_fAttackDT = 0.8f;
	m_moveTimer = 0;
	m_Rigidbody =CreateComponent<CRigidbody>();
	m_pGravity = CreateComponent<CGravity>();
	m_Collider = CreateComponent<CCollider>();
}

CRabbit::CRabbit(string name) : CEnemy(name)
{
	m_iDir = 1;
	m_attackCount = 0;
	m_fAttackTimer = 0;
	m_fAttackDT = 0.8f;
	m_moveTimer = 0;
	m_Rigidbody = CreateComponent<CRigidbody>();
	m_pGravity = CreateComponent<CGravity>();
	m_Collider = CreateComponent<CCollider>();
}

CRabbit::~CRabbit()
{
}

void CRabbit::Init()
{
	m_Rigidbody->SetFriction(700.0f);
	m_Rigidbody->SetMaxVelocity(vec2(300.0f, 1000.0f));
	m_pGravity->SetGravity(1700.0f);
	SetScale(vec2{ 75.f, 80.f });
	
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\NES - Mega Man 2 - Enemies.png";
	m_Animator->SetTexture("Enemy", strFilePath.c_str());
	CTexture* pTex = m_Animator->GetTexture();

	m_Animator->CreateAnimation("Rabbit_Idle_Right", pTex, vec2(124, 611), vec2(32, 38), vec2(0, 0), -1, 0.5f, 1);
	m_Animator->CreateAnimation("Rabbit_Idle_Left", pTex, vec2(124, 611), vec2(32, 38), vec2(0, 0), 1, 0.5f, 1);
	m_Animator->CreateAnimation("Rabbit_Jump_Right", pTex, vec2(190, 611), vec2(32, 38), vec2(-33, 0), -1, 0.1f, 1);
	m_Animator->CreateAnimation("Rabbit_Jump_Left", pTex, vec2(190, 611), vec2(32, 38), vec2(-33, 0), 1, 0.1f, 1);
	// x : 190 -> 157 -> 124 // 
	// 156 574
	m_fSpeed = 100;

	CEnemy::Init();
}

void CRabbit::Update()
{
	CGameObject::Update();
	
	m_moveTimer += fDT;
	// printf("Rabbit Pos : %f, %f\n", GetPos().x, GetPos().y);
	// printf("m_pGravity->GetGround() : %d\n", m_pGravity->GetGround());
	if (m_Rigidbody->GetVelocity().y < 0 && m_pGravity->GetGround() == false)
	{
		ChangeState(ENEMY_STATE::FALL);
	}

	// if (m_fAttackTimer > 5 && m_eCurState != RABBIT_STATE::JUMP)
	if (m_moveTimer > 6.f && m_eCurState != ENEMY_STATE::JUMP)
	{
		m_moveTimer = 0;
		Jump();
	}

	if (m_moveTimer > 3.f)
	{
		// 123
		// 딜레c이 1초
		// printf("m_attackCount : %d\n", m_attackCount);
		if (m_attackCount < 3)
		{
			m_fAttackTimer += fDT;
			if (m_fAttackTimer > m_fAttackDT)		// m_fAttackDT = 1
			{
				Attack();				// 발사기능. 0.8초 간격
				m_fAttackTimer = 0;
				++m_attackCount;
			}
		}
		// 5초보다 큰 동안에 m_attackCount = 3이 되면
		// 카운트를 0으로 만들어버리니 5초내내 쏘는거나 다름없다. 
	}
	else 
	{
		m_attackCount = 0;
		m_fAttackTimer = 0;
	}
	// printf("Rabbit State : %d\n", m_eCurState);
	UpdateState();

	ScreenOut();
}

void CRabbit::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;

	if (dynamic_cast<CCharacter*>(pOtherObj))
	{
		int dir = 0;

		dir = (pOtherObj->GetPos().x > GetPos().x) ? 1 : -1;
		// 플레이어에게 신호
		static_cast<CCharacter*>(pOtherObj)->TakeDamage(m_fDamage, dir);
	}
}

void CRabbit::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;

	if (dynamic_cast<CCharacter*>(pOtherObj))
	{
		int dir = 0;

		dir = (pOtherObj->GetPos().x > GetPos().x) ? 1 : -1;
		// 플레이어에게 신호
		static_cast<CCharacter*>(pOtherObj)->TakeDamage(m_fDamage, dir);
	}
}

void CRabbit::UpdateState()
{
	switch (m_eCurState)
	{
	case ENEMY_STATE::IDLE:
	{
		if (m_iDir == 1) m_Animator->Play("Rabbit_Idle_Right", true);
		else m_Animator->Play("Rabbit_Idle_Left", true);
		ChangeState(ENEMY_STATE::IDLE);
	}
		break;
	case ENEMY_STATE::JUMP:
	{
		if (m_iDir == 1) m_Animator->Play("Rabbit_Jump_Right", true);
		else m_Animator->Play("Rabbit_Jump_Left", true);
	}
		break;
	case ENEMY_STATE::FALL:
	{
		if (m_iDir == 1) m_Animator->Play("Rabbit_Jump_Right", true);
		else m_Animator->Play("Rabbit_Jump_Left", true);
		if (m_pGravity->GetGround()) ChangeState(ENEMY_STATE::IDLE);
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		if (m_iDir == 1)  m_Animator->Play("Rabbit_Idle_Right", true);
		else m_Animator->Play("Rabbit_Idle_Left", true);
		ChangeState(ENEMY_STATE::IDLE);
	}
		break;
	default:
		break;
	}
}

void CRabbit::Attack()
{
	// 주기가 있다. 

	// 방향 전환
	vec2 playerPos = GetPlayerPosition();
	vec2 dir = (playerPos - GetPos()).Normalize();
	m_iDir = dir.x > 0 ? 1 : -1;			// 방향이 반대
	
	// printf("playerPos : %f, %f \n", playerPos.x, playerPos.y);

	CEnemyProjectile* pBullet = new CEnemyProjectile();

	vec2 vBulletPos = GetPos();
	pBullet->SetPos(vBulletPos);		// 생성 위치(몬스터 앞)
	pBullet->SetSpeed(300.0f);
	pBullet->SetDir(dir);		// 플레이어 방향으로 발사

	CreateObject(pBullet, GROUP_TYPE::PROJ_ENEMY);
	// cout << "Shoot!" << '\n';
}

void CRabbit::Jump()
{
	// 점프 
	if (m_Rigidbody)
	{
		ChangeState(ENEMY_STATE::JUMP);
		m_Rigidbody->AddVelocity(vec2(1000.f * m_iDir, 800.f));
	}
}

void CRabbit::TakeDamage()
{
	DeleteObject(this);
}

