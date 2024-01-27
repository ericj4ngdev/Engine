#include "include.h"

// CComponent의 생성자를 자식 생성자 초기화로부터 호출
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_iDir(1)
	, m_iPrevDir(-1)
{
	// m_speed = 1000;	
	
}


ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Init()
{
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
	printf("m_eCurStste : %d\n", (int)m_eCurState);
	float move = 0;
	if (GetKeyHold(LEFT))
	{
		m_iDir = -1;
		if (m_eCurState != PLAYER_STATE::SIT)
		{
			move = m_iDir * m_speed;
			m_curpos.x += move * fDT;
			m_rigidbody->SetVelocity(vec2(move, m_rigidbody->GetVelocity().y));
		}
	}
	if (GetKeyHold(RIGHT))
	{
		m_iDir = 1;
		if (m_eCurState != PLAYER_STATE::SIT)
		{
			move = m_iDir * m_speed;
			m_curpos.x += move * fDT;
			m_rigidbody->SetVelocity(vec2(move, m_rigidbody->GetVelocity().y));
		}
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
		// 땅이면 
		if (m_pGravity->GetGround())
			ChangeState(PLAYER_STATE::SIT);
	}
	if(GetKeyUp(DOWN)) 
	{
		ChangeState(PLAYER_STATE::IDLE);
	}
	

	if (GetKeyDown(X)) 
	{
		SpecialAttack();
	}
	if (GetKeyDown(V))
	{
		
	}

	if (GetKeyDown(C) && m_eCurState != PLAYER_STATE::JUMP)
	{
		if (m_rigidbody && m_eCurState != PLAYER_STATE::SIT)
		{
			ChangeState(PLAYER_STATE::JUMP);
			// m_rigidbody->SetVelocity(vec2(m_rigidbody->GetVelocity().x, 800.f));
			m_rigidbody->AddVelocity(vec2(m_rigidbody->GetVelocity().x, 800.f));
		}
	}

	// printf("\x1B[H");
	// printf("\x1B[B");
	// printf("Player (%f, %f)\n", m_curpos.x, m_curpos.y);
	// set(현재 위치 + 변화량) 동기화.
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}

void ControllerComponent::SpecialAttack() {
	vec2 vSwordPos = gameObject->GetPos();
	vSwordPos.x += gameObject->GetScale().y / 2.f;
	
	CSword* pSword = new CSword("Sword");
	pSword->GetComponent<TransformComponent>()->SetPosition(vSwordPos);
	pSword->GetComponent<TransformComponent>()->SetScale(vec2(50.f, 50.f));
	pSword->GetComponent<Sword>()->SetDir(vec2(1,0));

	CreateObject(pSword, GROUP_TYPE::PROJ_PLAYER);
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
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Attack_Right", false);
		else
			gameObject->GetComponent<CAnimator>()->Play("Attack_Left", false);
		ChangeState(PLAYER_STATE::IDLE);
	}
	break;
	case PLAYER_STATE::SIT:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Sit_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Sit_Left", true);
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

// 모든 State 끝에 Idle로 돌아가는 로직 만들기
void ControllerComponent::ChangeState(PLAYER_STATE newState)
{
	// 이전 프레임과 비교
	if (m_eCurState == newState) return;
	m_eCurState = newState;
}

void ControllerComponent::UpdateAnimation()
{
	// printf("1. m_eCurStste : %d\r", (int)m_eCurState);
	// if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir) return;

	// 바뀌면
	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Idle_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Idle_Left", true);
	}
	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Walk_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Walk_Left", true);
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Jump_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Jump_Left", true);
	}
	break;
	case PLAYER_STATE::ATTACK:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Attack_Right", false);
		else
			gameObject->GetComponent<CAnimator>()->Play("Attack_Left", false);
	}
	break;
	case PLAYER_STATE::SIT:
	{
		if (m_iDir == 1)
			gameObject->GetComponent<CAnimator>()->Play("Sit_Right", true);
		else
			gameObject->GetComponent<CAnimator>()->Play("Sit_Left", true);
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
