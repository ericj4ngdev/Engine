#include "include.h"

// CComponent�� �����ڸ� �ڽ� ������ �ʱ�ȭ�κ��� ȣ��
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
	m_rigidbody = gameObject->GetComponent<CRigidbody>();	// ��� �� ������Ʈ�ؾ� �ϴ°�?
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

	printf("\x1B[H");
	printf("\x1B[B");
	// printf("Player (%f, %f)\n", m_curpos.x, m_curpos.y);
	// set(���� ��ġ + ��ȭ��)
	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}
