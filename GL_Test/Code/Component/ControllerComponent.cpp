#include "include.h"

// CComponent�� �����ڸ� �ڽ� ������ �ʱ�ȭ�κ��� ȣ��
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_iDir(1)
	, m_iPrevDir(-1)
	, m_bMoveable(true)
	, m_MoveOffset(0.1f)
	, m_attackTimer(1)
	, m_attackCount(0)
	, m_attackDT(0.1)
	, m_eCurAttackState(PLAYER_ATTACK_STATE::IDLE)
{
	// m_speed = 1000;
}

ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Init()
{
	// m_attackCount = 0;
	// animationTimer = 1;
	// m_attackDT = 0.3;
}

void ControllerComponent::Update()
{
	m_curpos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	m_rigidbody = gameObject->GetComponent<CRigidbody>();	// ��� �� ������Ʈ�ؾ� �ϴ°�?
	m_Collider = gameObject->GetComponent<CCollider>();
	m_pGravity = gameObject->GetComponent<CGravity>();
	
	Control();	
	UpdateState();

	vec2 vRenderPos = gameObject->GetComponent<CAnimator>()->GetAnimation()->GetRenderPos();

	/*if (vRenderPos.x <= 50)
	{
		m_curpos.x -= -m_speed * fDT;
		m_rigidbody->SetVelocity(vec2(m_speed, m_rigidbody->GetVelocity().y));
		printf("boundary");
	}
	if (vRenderPos.x >= GLMgr::g_screenWidth - 50) {
		m_curpos.x -= 1 * m_speed * fDT;
		m_rigidbody->SetVelocity(vec2(-m_speed, m_rigidbody->GetVelocity().y));
		printf("boundary");
	}*/

	printf("\x1B[H");
	printf("\x1B[B");
	// printf("ControllerComponent::Update() -> m_eCurStste : %d	m_eCurAttackState : %d\n", (int)m_eCurState, (int)m_eCurAttackState);
	// printf("ControllerComponent::Update() -> Player (%f, %f)\n", m_curpos.x, m_curpos.y);
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}

void ControllerComponent::FinalUpdate()
{
}

void ControllerComponent::Render()
{
	
}

void ControllerComponent::Destroy()
{

}

void ControllerComponent::Control()
{	
	float move = 0;

	bool moveLeft = GetKeyHold(LEFT);
	bool moveRight = GetKeyHold(RIGHT);

	if (moveLeft || moveRight) {
		// �¿� �̵� ó��
		if (moveLeft) {
			m_iDir = -1;
		}
		else {
			m_iDir = 1;
		}

		move = m_iDir * m_speed;
		m_curpos.x += move * fDT;
		// m_rigidbody->SetVelocity(vec2(move, m_rigidbody->GetVelocity().y));
	}

	/*if (GetKeyHold(LEFT))
	{
		m_iDir = -1;
		move = m_iDir * m_speed;
		m_curpos.x += move * fDT;
		m_rigidbody->SetVelocity(vec2(move, m_rigidbody->GetVelocity().y));		
	}
	else if (GetKeyHold(RIGHT))
	{
		m_iDir = 1;
		move = m_iDir * m_speed;
		m_curpos.x += move * fDT;
		m_rigidbody->SetVelocity(vec2(move, m_rigidbody->GetVelocity().y));		
	}*/

	if (abs(move) > m_MoveOffset)
	{
		if (m_eCurState == PLAYER_STATE::IDLE)
			ChangeState(PLAYER_STATE::WALK);
	}
	else
	{
		if (m_eCurState == PLAYER_STATE::WALK)
			ChangeState(PLAYER_STATE::IDLE);
	}
	
	

	// Fall ����
	if (m_rigidbody->GetVelocity().y < 0 && m_pGravity->GetGround() == false)
	{
		ChangeState(PLAYER_STATE::FALL);
	}

	if (GetKeyDown(C) && m_eCurState != PLAYER_STATE::JUMP
					  && m_eCurState != PLAYER_STATE::FALL)
	{
		// if (m_eCurState != PLAYER_STATE::ATTACK || m_eCurAttackState != PLAYER_ATTACK_STATE::JUMP_ATTACK)
		if (m_rigidbody)
		{
			ChangeState(PLAYER_STATE::JUMP);
			m_rigidbody->AddVelocity(vec2(m_rigidbody->GetVelocity().x, 800.f));
		}		
	}

	if (GetKeyHold(V))
	{
		if (m_attackCount < 3) 
		{
			m_attackTimer += fDT;
			if (m_attackTimer > m_attackDT)
			{
				SpecialAttack();				// �߻���. 0.3�� ����
				m_attackTimer = 0;
				m_attackCount++;
			}
			switch (m_eCurState)
			{
			case PLAYER_STATE::IDLE:
				ChangeAttackState(PLAYER_ATTACK_STATE::NORMAL);
				break;
			case PLAYER_STATE::WALK:
				ChangeAttackState(PLAYER_ATTACK_STATE::RUN_ATTACK);
				break;
			case PLAYER_STATE::JUMP:
				ChangeAttackState(PLAYER_ATTACK_STATE::JUMP_ATTACK);
				break;
			case PLAYER_STATE::FALL:
				ChangeAttackState(PLAYER_ATTACK_STATE::JUMP_ATTACK);
				break;
			case PLAYER_STATE::ATTACK:				
				break;
			default:
				break;
			}
			ChangeState(PLAYER_STATE::ATTACK);
		}
	}
	if (GetKeyUp(V)) 
	{
		// ��Ÿ�� ���� ���� ����
		ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
		m_attackTimer = 1;
		m_attackCount = 0;
	}
	

	if (m_curpos.x > 0 && m_curpos.x < 3000) 
	{
		CCamera::GetInstance()->SetTarget(gameObject);
	}
	else 
	{
		CCamera::GetInstance()->SetTarget(NULL);
	}

	// assert(gameObject->GetComponent<CAnimator>()->GetAnimation()->GetRenderPos());
	// if (gameObject->GetComponent<CAnimator>()->GetAnimation()->GetRenderPos()) { return; }
	// set(���� ��ġ + ��ȭ��) ����ȭ.	
}


void ControllerComponent::SpecialAttack() {
	vec2 vBulletPos = gameObject->GetPos();
	vBulletPos.x += (gameObject->GetScale().y / 2.f) * m_iDir;
	
	CBullet* pBullet = new CBullet("Bullet");
	pBullet->SetPos(vBulletPos);
	pBullet->GetComponent<Bullet>()->SetDir(vec2(m_iDir,0));

	CreateObject(pBullet, GROUP_TYPE::PROJ_PLAYER);
	// cout << "Shoot!" << '\n';
}

void ControllerComponent::UpdateState()
{
	// printf("m_eCurStste : %d\n", (int)m_eCurState);
	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Idle_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Idle_Left", true);
		ChangeState(PLAYER_STATE::IDLE);
	}
	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Walk_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Walk_Left", true);
		// ChangeState(PLAYER_STATE::IDLE);
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == 1) 		
			gameObject->GetComponent<CAnimator>()->Play("Jump_Right", true);			
		else		
			gameObject->GetComponent<CAnimator>()->Play("Jump_Left", true);	
		// Idle�� ���ƿ��� �ڵ�� Player�� OnCollision�� �ִ�. 
	}
	break;
	case PLAYER_STATE::ATTACK:
	{
		UpdateAttack();		
	}
	break;
	case PLAYER_STATE::FALL:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Fall_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Fall_Left", true);
		
		// CPlayer�� OnCollsionEnter�� ���ƿ��� �Ϸ� �ߴµ� ���� ������ Idle�� �ȵ��ƿ´�. 
		if(m_pGravity->GetGround()) ChangeState(PLAYER_STATE::IDLE);
	}
	break;
	case PLAYER_STATE::HIT:
		break;
	case PLAYER_STATE::DEAD:
		break;
	default:
		break;
	}
}

void ControllerComponent::UpdateAttack()
{
	switch (m_eCurAttackState)
	{
	case PLAYER_ATTACK_STATE::IDLE: 
	{
		animationTimer = 0;
		// ChangeState(PLAYER_STATE::IDLE);		// ���߿��� Idle�� ���ƿ��� �ȵȴ�.
		// �׷��� Jump_Attack���� ������ ChangeState(PLAYER_STATE::IDLE);�־���
		// �Ʒ� �ڵ� �߰� -> �ܹ� ���ݽ� �ִϸ��̼� �ȵ��ư�
		if(m_ePrevAttackState != PLAYER_ATTACK_STATE::JUMP_ATTACK)
			ChangeState(PLAYER_STATE::IDLE);
		else
			ChangeState(PLAYER_STATE::FALL);
	}
		break;
	case PLAYER_ATTACK_STATE::NORMAL:
	{
		animationTimer += fDT;
		// 0.5�� ���� �ִϸ��̼� 
		if (animationTimer < 0.5f) 
		{
			if (m_iDir == 1)
				gameObject->GetComponent<CAnimator>()->Play("Attack_Right", true);
			else
				gameObject->GetComponent<CAnimator>()->Play("Attack_Left", true);			
		}
		else 
		{
			// 0.5�� ������ ��(������ �־ ��)
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::IDLE);
			animationTimer = 0;			// ���� �ð� �ʱ�ȭ
			// �� �� Idle�̸� ���� �����ӿ��� PLAYER_STATE�� Attack�� �ƴϾ 
			// PLAYER_ATTACK_STATE�� IDLE�̾ animationTimer�� �ʱ�ȭ�� �ȵȴ�.
			// ���� Change�� ��, ��ü �ʱ�ȭ�� ����� �Ѵ� ����
		}	
	}
		break;
	case PLAYER_ATTACK_STATE::RUN_ATTACK:
	{
		animationTimer += fDT;
		if (animationTimer < 0.5f)
		{
			if (m_iDir == 1)
				gameObject->GetComponent<CAnimator>()->Play("Run_Attack_Right", true);
			else
				gameObject->GetComponent<CAnimator>()->Play("Run_Attack_Left", true);
		}
		else
		{
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::IDLE);
			animationTimer = 0;
		}
	}
		break;
	case PLAYER_ATTACK_STATE::JUMP_ATTACK:
	{
		animationTimer += fDT;
		if (animationTimer < 0.5f)
		{
			if (m_iDir == 1)
				gameObject->GetComponent<CAnimator>()->Play("Jump_Attack_Right", true);
			else
				gameObject->GetComponent<CAnimator>()->Play("Jump_Attack_Left", true);
		}
		else
		{
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::FALL);		// ���� ������ ������ Idle�� �ƴ� �������� ����. 
			// FALL���� �˾Ƽ� IDLE�� ���ư� ����
			animationTimer = 0;
		}
	}
		break;
	default:
		break;
	}

}

// ��� State ���� Idle�� ���ư��� ���� �����
void ControllerComponent::ChangeState(PLAYER_STATE newState)
{
	// ���� �����Ӱ� ��
	if (m_eCurState == newState) return;
	m_eCurState = newState;
}

void ControllerComponent::ChangeAttackState(PLAYER_ATTACK_STATE attackState)
{
	m_ePrevAttackState = m_eCurAttackState;
	if (m_eCurAttackState == attackState) return;
	m_eCurAttackState = attackState;
}