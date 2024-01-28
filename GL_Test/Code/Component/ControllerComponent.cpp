#include "include.h"

// CComponent의 생성자를 자식 생성자 초기화로부터 호출
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
	m_rigidbody = gameObject->GetComponent<CRigidbody>();	// 얘는 왜 업데이트해야 하는가?
	m_Collider = gameObject->GetComponent<CCollider>();
	m_pGravity = gameObject->GetComponent<CGravity>();
	
	Control();	
	UpdateState();
	// UpdateAnimation();
	/*printf("\x1B[H");
	printf("\x1B[B");*/
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
	
	

	// Fall 조건
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
				SpecialAttack();				// 발사기능. 0.3초 간격
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
			default:
				break;
			}
			ChangeState(PLAYER_STATE::ATTACK);
		}
	}
	if (GetKeyUp(V)) 
	{
		// 단타용
		// 떼면 완전 종료
		/*switch (m_eCurAttackState)
		{
		case PLAYER_ATTACK_STATE::IDLE:
		{

		}
		break;
		case PLAYER_ATTACK_STATE::NORMAL:
		{
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::IDLE);
		}
		break;
		case PLAYER_ATTACK_STATE::RUN_ATTACK:
		{
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::WALK);
		}
		break;
		case PLAYER_ATTACK_STATE::JUMP_ATTACK:
		{
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::FALL);
		}
		break;
		default:
			break;
		}*/
		ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
		m_attackTimer = 1;
		m_attackCount = 0;
	}

	

	printf("m_eCurStste : %d	m_eCurAttackState : %d\n", (int)m_eCurState, (int)m_eCurAttackState);
	
	// printf("Player (%f, %f)\n", m_curpos.x, m_curpos.y);
	// set(현재 위치 + 변화량) 동기화.
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
		// Idle로 돌아오는 코드는 Player의 OnCollision에 있다. 
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
		// 앉아있는 동안에는 Idle로 돌아가면 안된다. 
		// 따라서 아래 코드는 특정 조건에 의해 해제되게 해야 한다. 
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

void ControllerComponent::UpdateAttack()
{	
	
	switch (m_eCurAttackState)
	{
	case PLAYER_ATTACK_STATE::IDLE: 
	{
		animationTimer = 0;
		// ChangeState(PLAYER_STATE::IDLE);		// 공중에선 Idle로 돌아오면 안된다.
		// 그래서 Jump_Attack빼고 일일이 ChangeState(PLAYER_STATE::IDLE);넣어줌
		// if(m_ePrevAttackState != PLAYER_ATTACK_STATE::JUMP_ATTACK)
		// 	ChangeState(PLAYER_STATE::IDLE);
	}
		break;
	case PLAYER_ATTACK_STATE::NORMAL:
	{
		animationTimer += fDT;
		// 3초 동안 애니메이션 
		if (animationTimer < 0.5f) 
		{
			if (m_iDir == 1)
				gameObject->GetComponent<CAnimator>()->Play("Attack_Right", true);
			else
				gameObject->GetComponent<CAnimator>()->Play("Attack_Left", true);			
		}
		else 
		{
			// 1.5초 지나면 끝(누르고 있어도 끝)
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::IDLE);
		}	
	}
		break;
	case PLAYER_ATTACK_STATE::RUN_ATTACK:
	{
		animationTimer += fDT;
		// 3초 동안 애니메이션 
		if (animationTimer < 0.5f)
		{
			if (m_iDir == 1)
				gameObject->GetComponent<CAnimator>()->Play("Run_Attack_Right", true);
			else
				gameObject->GetComponent<CAnimator>()->Play("Run_Attack_Left", true);
		}
		else
		{
			// 3초 지나면 끝(누르고 있어도 끝)
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::IDLE);
		}
	}
		break;
	case PLAYER_ATTACK_STATE::JUMP_ATTACK:
	{
		animationTimer += fDT;
		// 3초 동안 애니메이션 
		if (animationTimer < 0.5f)
		{
			if (m_iDir == 1)
				gameObject->GetComponent<CAnimator>()->Play("Jump_Attack_Right", true);
			else
				gameObject->GetComponent<CAnimator>()->Play("Jump_Attack_Left", true);
		}
		else
		{
			// 3초 지나면 끝(누르고 있어도 끝)
			ChangeAttackState(PLAYER_ATTACK_STATE::IDLE);
			ChangeState(PLAYER_STATE::FALL);		// 공중 공격이 끝나면 Idle이 아닌 공중으로 복귀. 
			// FALL에서 알아서 IDLE로 돌아갈 거임
		}
	}
		break;
	default:
		break;
	}

}

// 모든 State 끝에 Idle로 돌아가는 로직 만들기
void ControllerComponent::ChangeState(PLAYER_STATE newState)
{
	// 이전 프레임과 비교
	if (m_eCurState == newState) return;
	m_eCurState = newState;
}

void ControllerComponent::ChangeAttackState(PLAYER_ATTACK_STATE attackState)
{
	m_ePrevAttackState = m_eCurAttackState;
	if (m_eCurAttackState == attackState) return;
	m_eCurAttackState = attackState;
}