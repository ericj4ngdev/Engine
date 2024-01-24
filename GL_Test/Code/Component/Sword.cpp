#include "include.h"

COMPONENT_CONSTRUCTOR(Sword) ,m_vDirection(vec2(0,0))
{
	m_speed = 500;
}

void Sword::Init()
{
}

void Sword::Update()
{
	// Į ���� ��ġ �޾ƿ���. �׷��� �׻� 0,0�̴�...
	m_curpos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	Movement();
	printf("Sword (%f, %f)\n", m_curpos.x, m_curpos.y);
}

void Sword::FinalUpdate()
{

}

void Sword::Render()
{

}

void Sword::Destroy()
{

}

Sword::~Sword()
{

}

void Sword::Movement()
{
	m_curpos += m_vDirection * m_speed * fDT;

	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}
