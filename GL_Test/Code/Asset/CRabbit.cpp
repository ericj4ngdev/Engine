#include "include.h"
#include "CRabbit.h"

CRabbit::CRabbit()
{
	m_iDir = 1;
	m_attackCount = 0;
	m_attackTimer = 0;
	m_attackDT = 0.8f;
	m_moveTimer = 0;
	m_eCurState = RABBIT_STATE::IDLE;
	Init();
}

CRabbit::CRabbit(string name)
{
	m_iDir = 1;
	m_attackCount = 0;
	m_attackTimer = 0;
	m_attackDT = 0.8f;
	m_moveTimer = 0;
	m_eCurState = RABBIT_STATE::IDLE;
	Init();
}

CRabbit::~CRabbit()
{
}

void CRabbit::Init()
{
	CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	CreateComponent<CCollider>();
	CreateComponent<CAnimator>();

	GetComponent<CRigidbody>()->SetFriction(700.0f);
	GetComponent<CRigidbody>()->SetMaxVelocity(vec2(300.0f, 1000.0f));
	GetComponent<CGravity>()->SetGravity(1700.0f);
	SetScale(vec2{ 75.f, 80.f });
	
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\NES - Mega Man 2 - Enemies.png";
	GetComponent<CAnimator>()->SetTexture("Enemy", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();

	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Idle_Left", pTex, vec2(124, 611), vec2(32, 38), vec2(0, 0), 1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Idle_Right", pTex, vec2(124, 611), vec2(32, 38), vec2(0, 0), -1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Jump_Left", pTex, vec2(190, 611), vec2(32, 38), vec2(-33, 0), 1, 0.1f, 1);
	// x : 190 -> 157 -> 124 // 
	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Jump_Right", pTex, vec2(190, 611), vec2(32, 38), vec2(-33, 0), -1, 0.1f, 1);
	// 156 574
	m_fSpeed = 100;
}

void CRabbit::Update()
{
	CGameObject::Update();
	
	m_rigidbody = GetComponent<CRigidbody>();	// 얘는 왜 업데이트해야 하는가?
	m_Collider = GetComponent<CCollider>();
	m_pGravity = GetComponent<CGravity>();

	
	m_moveTimer += fDT;
	// printf("Rabbit Pos : %f, %f\n", GetPos().x, GetPos().y);
	// printf("m_pGravity->GetGround() : %d\n", m_pGravity->GetGround());
	if (m_rigidbody->GetVelocity().y < 0 && m_pGravity->GetGround() == false)
	{
		ChangeState(RABBIT_STATE::FALL);
	}

	// if (m_attackTimer > 5 && m_eCurState != RABBIT_STATE::JUMP)
	if (m_moveTimer > 6.f && m_eCurState != RABBIT_STATE::JUMP)
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
			m_attackTimer += fDT;
			if (m_attackTimer > m_attackDT)		// m_attackDT = 1
			{
				Attack();				// 발사기능. 0.8초 간격
				m_attackTimer = 0;
				++m_attackCount;
			}
		}
		// 5초보다 큰 동안에 m_attackCount = 3이 되면
		// 카운트를 0으로 만들어버리니 5초내내 쏘는거나 다름없다. 
	}
	else 
	{
		m_attackCount = 0;
		m_attackTimer = 0;
	}
	// printf("Rabbit State : %d\n", m_eCurState);
	UpdateState();

	vec2 vRenderPos = GetComponent<CAnimator>()->GetAnimation()->GetRenderPos();
	// printf("vRenderPos.x : %f\n", vRenderPos.x);
	if (vRenderPos.x <= -1 || vRenderPos.x >= GLMgr::g_screenWidth)
	{
		DeleteObject(this);
		// printf("CBullet::Update() -> Deleted\n");
	}

	// m_moveTimer += fDT;
	//if (m_moveTimer > 3.f) 
	//{
	//	// 착지하면 Idle
	//	GetComponent<CAnimator>()->Play("Rabbit_Idle_Left", true);
	//	// 딜레이 1초
	//	if (m_attackCount < 3)
	//	{
	//		m_attackTimer += fDT;
	//		if (m_attackTimer > m_attackDT)		// m_attackDT = 1
	//		{
	//			Attack();				// 발사기능. 1초 간격
	//			m_attackTimer = 0;
	//			m_attackCount++;
	//		}
	//	}
	//	else 
	//	{
	//		m_attackCount = 0;
	//		m_attackTimer = 0;
	//		m_attackDT = 1;
	//		m_moveTimer = -1;
	//	}
	//}
}

void CRabbit::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;
	if (dynamic_cast<CBullet*>(pOtherObj))
	{
		m_bAlive = false;
		// DeleteObject(this);
	}

	if (dynamic_cast<CPlayer*>(pOtherObj))
	{
		// 플레이어에게 신호?
		static_cast<CPlayer*>(pOtherObj)->TakeDamage(m_fDamage);
	}
}

void CRabbit::UpdateState()
{
	switch (m_eCurState)
	{
	case RABBIT_STATE::IDLE:
	{
		if (m_iDir == 1) GetComponent<CAnimator>()->Play("Rabbit_Idle_Left", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Idle_Right", true);
		ChangeState(RABBIT_STATE::IDLE);
	}
		break;
	case RABBIT_STATE::JUMP:
	{
		if (m_iDir == 1) GetComponent<CAnimator>()->Play("Rabbit_Jump_Left", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Jump_Right", true);
	}
		break;
	case RABBIT_STATE::FALL:
	{
		if (m_iDir == 1) GetComponent<CAnimator>()->Play("Rabbit_Jump_Left", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Jump_Right", true);
		if (m_pGravity->GetGround()) ChangeState(RABBIT_STATE::IDLE);
	}
	break;
	case RABBIT_STATE::ATTACK:
	{
		if (m_iDir == 1) GetComponent<CAnimator>()->Play("Rabbit_Idle_Left", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Idle_Right", true);
		ChangeState(RABBIT_STATE::IDLE);
	}
		break;
	default:
		break;
	}
}

void CRabbit::ChangeState(RABBIT_STATE newState)
{
	// 이전 프레임과 비교
	if (m_eCurState == newState) return;
	m_eCurState = newState;
}

void CRabbit::Attack()
{
	// 주기가 있다. 

	// 방향 전환
	vec2 playerPos = GetPlayerPosition();
	vec2 dir = (playerPos - GetPos()).Normalize();
	m_iDir = dir.x > 0 ? -1 : 1;			// 방향이 반대
	
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
	if (m_rigidbody)
	{
		ChangeState(RABBIT_STATE::JUMP);
		m_rigidbody->AddVelocity(vec2(1000.f * -m_iDir, 800.f));
	}
}

