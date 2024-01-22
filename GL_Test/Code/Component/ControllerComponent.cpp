#include "include.h"

// CComponent의 생성자를 자식 생성자 초기화로부터 호출
ControllerComponent::ControllerComponent(CGameObject* l_gameObject) : CComponent("ControllerComponent", l_gameObject)
{
	// m_pos = { 0, 0 };
}


ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Init()
{
	//m_pos.x = gameObject->GetTransform()->m_position.x;
	//m_pos.y = gameObject->GetTransform()->m_position.y;
}

void ControllerComponent::Update()
{
	// m_pos.x = gameObject->GetTransform()->m_position.x;
	// m_pos.y = gameObject->GetTransform()->m_position.y;
	// Control();	
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
	// m_pos = gameObject->GetTransform()->m_position;
	if (GetKeyHold(W))
	{
		m_pos.y += 1.f * fDT;
		printf("%f\n", m_pos.y);
	}
	if (GetKeyHold(A))
	{
		m_pos.x -= 1.f * fDT;
		printf("%f\n", m_pos.x);
	}
	if (GetKeyHold(S))
	{
		m_pos.y -= 1.f * fDT;
		printf("%f\n", m_pos.y);
	}
	if (GetKeyHold(D))
	{
		m_pos.x += 1.f * fDT;
		printf("%f\n", m_pos.x);
	}
	// gameObject->GetComponent<TransformComponent>()->SetPosition(m_pos.x, m_pos.y);
}
