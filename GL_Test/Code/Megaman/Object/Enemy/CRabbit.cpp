#include "include.h"

CRabbit::CRabbit()
{
	m_iDir = 1;
	m_attackCount = 0;
	m_fAttackTimer = 0;
	m_fAttackDT = 0.8f;
	m_moveTimer = 0;
	CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	CreateComponent<CCollider>();
	CreateComponent<CAnimator>();
}

CRabbit::CRabbit(string name) : CEnemy(name)
{
	m_iDir = 1;
	m_attackCount = 0;
	m_fAttackTimer = 0;
	m_fAttackDT = 0.8f;
	m_moveTimer = 0;
	CreateComponent<CRigidbody>();
	CreateComponent<CGravity>();
	CreateComponent<CCollider>();
	CreateComponent<CAnimator>();
}

CRabbit::~CRabbit()
{
}

void CRabbit::Init()
{
	GetComponent<CRigidbody>()->SetFriction(700.0f);
	GetComponent<CRigidbody>()->SetMaxVelocity(vec2(300.0f, 1000.0f));
	GetComponent<CGravity>()->SetGravity(1700.0f);
	SetScale(vec2{ 75.f, 80.f });
	
	std::string strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += "texture\\NES - Mega Man 2 - Enemies.png";
	GetComponent<CAnimator>()->SetTexture("Enemy", strFilePath.c_str());
	CTexture* pTex = GetComponent<CAnimator>()->GetTexture();

	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Idle_Right", pTex, vec2(124, 611), vec2(32, 38), vec2(0, 0), -1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Idle_Left", pTex, vec2(124, 611), vec2(32, 38), vec2(0, 0), 1, 0.5f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Jump_Right", pTex, vec2(190, 611), vec2(32, 38), vec2(-33, 0), -1, 0.1f, 1);
	GetComponent<CAnimator>()->CreateAnimation("Rabbit_Jump_Left", pTex, vec2(190, 611), vec2(32, 38), vec2(-33, 0), 1, 0.1f, 1);
	// x : 190 -> 157 -> 124 // 
	// 156 574
	m_fSpeed = 100;

	CEnemy::Init();
}

void CRabbit::Update()
{
	CGameObject::Update();
	
	m_rigidbody = GetComponent<CRigidbody>();	// ��� �� ������Ʈ�ؾ� �ϴ°�?
	m_Collider = GetComponent<CCollider>();
	m_pGravity = GetComponent<CGravity>();

	
	m_moveTimer += fDT;
	// printf("Rabbit Pos : %f, %f\n", GetPos().x, GetPos().y);
	// printf("m_pGravity->GetGround() : %d\n", m_pGravity->GetGround());
	if (m_rigidbody->GetVelocity().y < 0 && m_pGravity->GetGround() == false)
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
		// ����c�� 1��
		// printf("m_attackCount : %d\n", m_attackCount);
		if (m_attackCount < 3)
		{
			m_fAttackTimer += fDT;
			if (m_fAttackTimer > m_fAttackDT)		// m_fAttackDT = 1
			{
				Attack();				// �߻���. 0.8�� ����
				m_fAttackTimer = 0;
				++m_attackCount;
			}
		}
		// 5�ʺ��� ū ���ȿ� m_attackCount = 3�� �Ǹ�
		// ī��Ʈ�� 0���� ���������� 5�ʳ��� ��°ų� �ٸ�����. 
	}
	else 
	{
		m_attackCount = 0;
		m_fAttackTimer = 0;
	}
	// printf("Rabbit State : %d\n", m_eCurState);
	UpdateState();

	ScreenOut();

	// m_moveTimer += fDT;
	//if (m_moveTimer > 3.f) 
	//{
	//	// �����ϸ� Idle
	//	GetComponent<CAnimator>()->Play("Rabbit_Idle_Left", true);
	//	// ������ 1��
	//	if (m_attackCount < 3)
	//	{
	//		m_fAttackTimer += fDT;
	//		if (m_fAttackTimer > m_fAttackDT)		// m_fAttackDT = 1
	//		{
	//			Attack();				// �߻���. 1�� ����
	//			m_fAttackTimer = 0;
	//			m_attackCount++;
	//		}
	//	}
	//	else 
	//	{
	//		m_attackCount = 0;
	//		m_fAttackTimer = 0;
	//		m_fAttackDT = 1;
	//		m_moveTimer = -1;
	//	}
	//}
}

void CRabbit::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;

	if (dynamic_cast<CPlayer*>(pOtherObj))
	{
		int dir = 0;

		dir = (pOtherObj->GetPos().x > GetPos().x) ? 1 : -1;
		// �÷��̾�� ��ȣ
		static_cast<CPlayer*>(pOtherObj)->TakeDamage(m_fDamage, dir);
	}
}

void CRabbit::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->gameObject;

	if (dynamic_cast<CPlayer*>(pOtherObj))
	{
		int dir = 0;

		dir = (pOtherObj->GetPos().x > GetPos().x) ? 1 : -1;
		// �÷��̾�� ��ȣ
		static_cast<CPlayer*>(pOtherObj)->TakeDamage(m_fDamage, dir);
	}
}

void CRabbit::UpdateState()
{
	switch (m_eCurState)
	{
	case ENEMY_STATE::IDLE:
	{
		if (m_iDir == 1) GetComponent<CAnimator>()->Play("Rabbit_Idle_Right", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Idle_Left", true);
		ChangeState(ENEMY_STATE::IDLE);
	}
		break;
	case ENEMY_STATE::JUMP:
	{
		if (m_iDir == 1) GetComponent<CAnimator>()->Play("Rabbit_Jump_Right", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Jump_Left", true);
	}
		break;
	case ENEMY_STATE::FALL:
	{
		if (m_iDir == 1) GetComponent<CAnimator>()->Play("Rabbit_Jump_Right", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Jump_Left", true);
		if (m_pGravity->GetGround()) ChangeState(ENEMY_STATE::IDLE);
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		if (m_iDir == 1)  GetComponent<CAnimator>()->Play("Rabbit_Idle_Right", true);
		else GetComponent<CAnimator>()->Play("Rabbit_Idle_Left", true);
		ChangeState(ENEMY_STATE::IDLE);
	}
		break;
	default:
		break;
	}
}

void CRabbit::Attack()
{
	// �ֱⰡ �ִ�. 

	// ���� ��ȯ
	vec2 playerPos = GetPlayerPosition();
	vec2 dir = (playerPos - GetPos()).Normalize();
	m_iDir = dir.x > 0 ? 1 : -1;			// ������ �ݴ�
	
	// printf("playerPos : %f, %f \n", playerPos.x, playerPos.y);

	CEnemyProjectile* pBullet = new CEnemyProjectile();

	vec2 vBulletPos = GetPos();
	pBullet->SetPos(vBulletPos);		// ���� ��ġ(���� ��)
	pBullet->SetSpeed(300.0f);
	pBullet->SetDir(dir);		// �÷��̾� �������� �߻�

	CreateObject(pBullet, GROUP_TYPE::PROJ_ENEMY);
	// cout << "Shoot!" << '\n';
}

void CRabbit::Jump()
{
	// ���� 
	if (m_rigidbody)
	{
		ChangeState(ENEMY_STATE::JUMP);
		m_rigidbody->AddVelocity(vec2(1000.f * m_iDir, 800.f));
	}
}

void CRabbit::TakeDamage()
{
	DeleteObject(this);
}

