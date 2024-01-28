#include "include.h"

// CComponent�� �����ڸ� �ڽ� ������ �ʱ�ȭ�κ��� ȣ��
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_iDir(1)
	, m_iPrevDir(-1)
	, m_bMoveable(true)
	, m_attackTimer(1)
	, m_attackCount(0)
	, m_attackDT(0.1)
	, m_eCurAttackState(PLAYER_ATTACK_STATE::NORMAL)
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
	// UpdateAnimation();
	printf("\x1B[H");
	printf("\x1B[B");
	// m_ePrevState = m_eCurState;
	// m_iPrevDir = m_iDir;
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
	// printf("m_eCurStste : %d\n", (int)m_eCurState);
	float move = 0;
	if (GetKeyHold(LEFT))
	{
		m_iDir = -1;
		move = m_iDir * m_speed;
		m_curpos.x += move * fDT;
		m_rigidbody->SetVelocity(vec2(move, m_rigidbody->GetVelocity().y));		
	}
	if (GetKeyHold(RIGHT))
	{
		m_iDir = 1;
		move = m_iDir * m_speed;
		m_curpos.x += move * fDT;
		m_rigidbody->SetVelocity(vec2(move, m_rigidbody->GetVelocity().y));
		
	}

	if (abs(move) > 0)
	{
		if (m_eCurState == PLAYER_STATE::IDLE)
			ChangeState(PLAYER_STATE::WALK);
	}
	else
	{
		if (m_eCurState == PLAYER_STATE::WALK)
			ChangeState(PLAYER_STATE::IDLE);
	}
	
	

	if (GetKeyHold(DOWN))
	{

	}
	if(GetKeyUp(DOWN)) 
	{

	}
	

	if (GetKeyDown(X)) 
	{
		// 
	}
	if (GetKeyHold(V))
	{
		// ���� �������� JUMP, FALL �̸� (�����̸�)
		if (m_eCurState == PLAYER_STATE::JUMP || m_eCurState == PLAYER_STATE::FALL) 
		{
			// ���� ����
		}

		// IDLE�̾��ٸ�
		if (m_eCurState == PLAYER_STATE::IDLE)
		{
			// m_bMoveable = false;
			if (m_attackCount < 3) {
				if (m_attackTimer > m_attackDT)
				{
					SpecialAttack();				// �߻���. 0.3�� ����
					m_attackTimer = 0;
					m_attackCount++;
				}
				m_attackTimer += fDT;
				ChangeAttackState(PLAYER_ATTACK_STATE::NORMAL);
				ChangeState(PLAYER_STATE::ATTACK);
				// 3�� �߻��� V ���� ī��Ʈ �ʱ�ȭ
				// m_attackCount = 0;
			}			
		}
	}
	if (GetKeyUp(V)) 
	{
		// ���� ���� ����
		ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
		ChangeState(PLAYER_STATE::IDLE);
		m_attackTimer = 1;
		m_attackCount = 0;
	}

	if (GetKeyDown(C) && m_eCurState != PLAYER_STATE::JUMP)
	{
		if (m_rigidbody && m_eCurState != PLAYER_STATE::SIT)
		{
			ChangeState(PLAYER_STATE::JUMP);
			m_rigidbody->AddVelocity(vec2(m_rigidbody->GetVelocity().x, 800.f));
		}
	}

	
	// printf("Player (%f, %f)\n", m_curpos.x, m_curpos.y);
	// set(���� ��ġ + ��ȭ��) ����ȭ.
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}

void ControllerComponent::SpecialAttack() {
	vec2 vBulletPos = gameObject->GetPos();
	vBulletPos.x += (gameObject->GetScale().y / 2.f) * m_iDir;
	
	CBullet* pBullet = new CBullet("Bullet");
	pBullet->GetComponent<TransformComponent>()->SetPosition(vBulletPos);
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
	case PLAYER_STATE::SIT:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Sit_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Sit_Left", true);
		// �ɾ��ִ� ���ȿ��� Idle�� ���ư��� �ȵȴ�. 
		// ���� �Ʒ� �ڵ�� Ư�� ���ǿ� ���� �����ǰ� �ؾ� �Ѵ�. 
		// ChangeState(PLAYER_STATE::IDLE);
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

void ControllerComponent::UpdateAnimation()
{
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
	if (m_eCurAttackState == attackState) return;
	m_eCurAttackState = attackState;
}

void ControllerComponent::UpdateAttack()
{	
	switch (m_eCurAttackState)
	{
	case PLAYER_ATTACK_STATE::IDLE: 
	{
		animationTimer = 0;
		ChangeState(PLAYER_STATE::IDLE);
	}
		break;
	case PLAYER_ATTACK_STATE::NORMAL:
	{
		animationTimer += fDT;
		// 3�� ���� �ִϸ��̼� 
		if (animationTimer < 1.5f) 
		{
			if (m_iDir == 1)
				gameObject->GetComponent<CAnimator>()->Play("Attack_Right", true);
			else
				gameObject->GetComponent<CAnimator>()->Play("Attack_Left", true);			
		}
		else 
		{
			// 3�� ������ ��(������ �־ ��)
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
		}	
	}
		break;
	case PLAYER_ATTACK_STATE::RUN_ATTACK:
		break;
	case PLAYER_ATTACK_STATE::JUMP_ATTACK:
		break;
	default:
		break;
	}
	
	
	int cur = gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->GetCurFrame();
	int max = gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->GetMaxFrame();
	if ( cur >= max - 1)
	{
		animationTimer = 0.5;
		m_bMoveable = true;
		gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->SetFinished(false);
		ChangeState(PLAYER_STATE::IDLE);
	}


}
