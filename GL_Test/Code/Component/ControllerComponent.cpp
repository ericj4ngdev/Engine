#include "include.h"

// CComponent�� �����ڸ� �ڽ� ������ �ʱ�ȭ�κ��� ȣ��
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
	m_rigidbody = gameObject->GetComponent<CRigidbody>();	// ��� �� ������Ʈ�ؾ� �ϴ°�?
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
		// ���� ä�� �̵� X
		// ���� ���°� �ƴϸ� �̵�
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
	// set(���� ��ġ + ��ȭ��) ����ȭ.
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
	// ���� ����
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
		// ���� �߿� �¿�Ű ������ ���� ��� ����
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

		// ó������ false, State�� Attack�� �ǰ� �ð��� ������ true�Ǿ ���빰 ����
		if (gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->IsFinished()) 
		{
			// �ٽ� ���� �ְ� 
			gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Right")->SetFinished(false);
		}
		if (gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Left")->IsFinished())
		{
			// �ٽ� ���� �ְ� 
			gameObject->GetComponent<CAnimator>()->FindAnimation("Attack_Left")->SetFinished(false);
		}
	}
	

	// ���� ���� bool ����
	if (GetKeyDown(C) && m_eCurState != PLAYER_STATE::JUMP)
	{
		// ���� ä���� ���� �Ұ�
		if (m_rigidbody && m_eCurState != PLAYER_STATE::SIT)
		{			
			m_rigidbody->AddVelocity(vec2(m_rigidbody->GetVelocity().x, 700.f));	// ������

			//if (m_rigidbody->GetVelocity().x > 0) {
			//	// m_rigidbody->AddVelocity(vec2(500.f, 700.f));	// ������
			//}
			//else if (m_rigidbody->GetVelocity().x < 0) 
			//{
			//	// m_rigidbody->AddVelocity(vec2(-500.f, 700.f));	// ������
			//}
			//else {
			//	// m_rigidbody->AddVelocity(vec2(0.f, 700.f));	// ������
			//}
			printf("m_rigidbody->GetVelocity().x : %f\n", m_rigidbody->GetVelocity().x);
		}
		m_eCurState = PLAYER_STATE::JUMP;
	}

	//if (m_pGravity->GetGround() == false) // ����
	//{
	//	if (m_rigidbody->GetVelocity().x > 0) {
	//		m_rigidbody->AddVelocity(vec2(1000.f, 0.f));
	//		// m_rigidbody->AddVelocity(vec2(10000.f, 0.f));	// ������
	//	}
	//	else if (m_rigidbody->GetVelocity().x < 0)
	//	{
	//		m_rigidbody->AddVelocity(vec2(-500.f, 0.f));	// ������
	//	}
	//	else {
	//		m_rigidbody->AddVelocity(vec2(0.f, 0.f));	// ������
	//	}
	//}

	if (GetKeyHold(DOWN))
	{
		// ���̸� 
		if(m_pGravity->GetGround())
			m_eCurState = PLAYER_STATE::SIT;
		// �ٸ� Ű ������ �ƹ� ��������
		// ��, ������ ����		
	}
	if (GetKeyUp(DOWN))
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	float speed = m_rigidbody->GetSpeed();
	
	
	// printf("speed : %f\n", speed);
	printf("1. m_eCurStste : %d\n", (int)m_eCurState);
	// ���� �߿� IDle����
	// �ӵ� ���� �ֱ�
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
	
	// �ٲ��
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
