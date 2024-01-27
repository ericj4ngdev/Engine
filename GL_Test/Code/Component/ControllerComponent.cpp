#include "include.h"

// CComponent의 생성자를 자식 생성자 초기화로부터 호출
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
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
	UpdateAnimation();
	
	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
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
	//if (GetKeyHold(W))
	//{		
	//	m_curpos.y += m_speed * fDT;
	//	// m_rigidbody->AddForce(vec2(0.f, m_speed));
	//}

	if (GetKeyHold(LEFT))
	{
		// m_curpos.x -= m_speed * fDT;
		// m_rigidbody->AddVelocity(vec2(-m_speed, 0.f));
		// m_rigidbody->AddForce(vec2(- m_speed, 0.f));
		// 앉은 채로 이동 X
		// 앉은 상태가 아니면 이동
		if (m_eCurState != PLAYER_STATE::SIT)
		{
			m_curpos.x -= m_speed * fDT;
			m_rigidbody->SetVelocity(vec2(-m_speed, m_rigidbody->GetVelocity().y));
		}
	}
	if (GetKeyHold(DOWN))
	{
		if (m_pGravity->GetGround()) 
		{
			//vec2 vScale = gameObject->GetScale();
			//m_Collider->SetScale(vec2(vScale.x, vScale.y * 0.75));
			//m_curpos.y -= vScale.y * 0.125;
		}		
		// m_rigidbody->AddForce(vec2(0.f, - m_speed));
	}
	if (GetKeyUp(DOWN))
	{
		if (m_ePrevState == PLAYER_STATE::SIT) 
		{
			//vec2 vScale = gameObject->GetScale();
			//m_curpos.y += vScale.y * 0.125;
			//m_Collider->SetScale(vec2(vScale.x, vScale.y));
		}
	}
	if (GetKeyHold(RIGHT))
	{
		if (m_eCurState != PLAYER_STATE::SIT)
		{
			m_curpos.x += m_speed * fDT;  // m_rigidbody->AddForce(vec2(m_speed, 0.f));
			m_rigidbody->SetVelocity(vec2(m_speed, m_rigidbody->GetVelocity().y));
		}
	}
	//if (GetKeyDown(W))
	//{
	//	// m_curpos.y += m_speed * fDT;
	//	m_rigidbody->AddVelocity(vec2(0.f, m_speed / 2));
	//}
	//if (GetKeyDown(A))
	//{
	//	// m_curpos.x -= m_speed * fDT;
	//	m_rigidbody->AddVelocity(vec2(- m_speed / 2, 0.f));
	//}
	//if (GetKeyDown(S))
	//{
	//	// m_curpos.y -= m_speed * fDT;
	//	m_rigidbody->AddVelocity(vec2(0.f, - m_speed / 2));
	//}
	//if (GetKeyDown(D))
	//{
	//	// m_curpos.x += m_speed * fDT;
	//	m_rigidbody->AddVelocity(vec2(m_speed / 2, 0.f));
	//}
	if (GetKeyDown(X)) 
	{
		SpecialAttack();
	}
	if (GetKeyDown(V))
	{
		
	}
	if (GetKeyDown(C))
	{
		// SpecialAttack();
	}

	printf("\x1B[H");
	printf("\x1B[B");
	printf("Player (%f, %f)\n", m_curpos.x, m_curpos.y);
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
	// 상태 관리
	if (GetKeyHold(LEFT))
	{
		if (m_eCurState != PLAYER_STATE::JUMP 
			&& m_eCurState != PLAYER_STATE::SIT 
			&& m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_iDir = -1;
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (GetKeyHold(RIGHT))
	{
		// 점프 중에 좌우키 눌러도 점프 모션 유지
		if (m_eCurState != PLAYER_STATE::JUMP 
			&& m_eCurState != PLAYER_STATE::SIT 
			&& m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_iDir = 1;
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (GetKeyDown(V))
	{
		m_eCurState = PLAYER_STATE::ATTACK;

		// 처음에는 false, State가 Attack이 되고 시간이 지나면 true되어서 내용물 실행
		if (gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->IsFinished()) 
		{
			// 다시 쓸수 있게 
			gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->SetFinished(false);
		}
		if (gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Left")->IsFinished())
		{
			// 다시 쓸수 있게 
			gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Left")->SetFinished(false);
		}
	}
	

	// 점프 관련 bool 변수
	if (GetKeyDown(C) && m_eCurState != PLAYER_STATE::JUMP)
	{
		// 앉은 채에서 점프 불가
		if (m_rigidbody && m_eCurState != PLAYER_STATE::SIT)
		{			
			m_rigidbody->AddVelocity(vec2(m_rigidbody->GetVelocity().x, 700.f));	// 점프력

			//if (m_rigidbody->GetVelocity().x > 0) {
			//	// m_rigidbody->AddVelocity(vec2(500.f, 700.f));	// 점프력
			//}
			//else if (m_rigidbody->GetVelocity().x < 0) 
			//{
			//	// m_rigidbody->AddVelocity(vec2(-500.f, 700.f));	// 점프력
			//}
			//else {
			//	// m_rigidbody->AddVelocity(vec2(0.f, 700.f));	// 점프력
			//}
			printf("m_rigidbody->GetVelocity().x : %f\n", m_rigidbody->GetVelocity().x);
		}
		m_eCurState = PLAYER_STATE::JUMP;
	}

	//if (m_pGravity->GetGround() == false) // 공중
	//{
	//	if (m_rigidbody->GetVelocity().x > 0) {
	//		m_rigidbody->AddVelocity(vec2(1000.f, 0.f));
	//		// m_rigidbody->AddVelocity(vec2(10000.f, 0.f));	// 점프력
	//	}
	//	else if (m_rigidbody->GetVelocity().x < 0)
	//	{
	//		m_rigidbody->AddVelocity(vec2(-500.f, 0.f));	// 점프력
	//	}
	//	else {
	//		m_rigidbody->AddVelocity(vec2(0.f, 0.f));	// 점프력
	//	}
	//}

	if (GetKeyHold(DOWN))
	{
		// 땅이면 
		if(m_pGravity->GetGround())
			m_eCurState = PLAYER_STATE::SIT;
		// 다른 키 눌러도 아무 반응없게
		// 단, 공격은 가능		
	}
	if (GetKeyUp(DOWN))
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	float speed = m_rigidbody->GetSpeed();
	
	
	// printf("speed : %f\n", speed);
	printf("1. m_eCurStste : %d\n", (int)m_eCurState);
	// 점프 중에 IDle방지
	// 속도 조건 넣기
	if (m_rigidbody->GetSpeed() <= 1 && PLAYER_STATE::JUMP != m_eCurState && PLAYER_STATE::SIT != m_eCurState && m_eCurState != PLAYER_STATE::ATTACK)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	if (gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->IsFinished())
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	if (gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Left")->IsFinished())
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	printf("2. m_eCurStste : %d\n", (int)m_eCurState);
}

void ControllerComponent::UpdateAnimation()
{
	// printf("1. m_eCurStste : %d\r", (int)m_eCurState);
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir) return;
	
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
