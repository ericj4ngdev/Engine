#include "include.h"

// CComponent의 생성자를 자식 생성자 초기화로부터 호출
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
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
	Control();	
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
	if (GetKeyHold(A))
	{
		m_curpos.x -= m_speed * fDT;
		// m_rigidbody->AddForce(vec2(- m_speed, 0.f));
	}
	//if (GetKeyHold(S))
	//{
	//	m_curpos.y -= m_speed * fDT;
	//	// m_rigidbody->AddForce(vec2(0.f, - m_speed));
	//}
	if (GetKeyHold(D))
	{
		m_curpos.x += m_speed * fDT;
		// m_rigidbody->AddForce(vec2(m_speed, 0.f));
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

	if (GetKeyDown(Z)) 
	{
		SpecialAttack();
	}

	if (GetKeyDown(SPACE))
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
	cout << "Shoot!" << '\n';
}