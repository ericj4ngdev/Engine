#include "include.h"


Zombie::Zombie(CGameObject* l_gameObject) : CComponent("Zombie", l_gameObject)
{
	
}

Zombie::~Zombie()
{
}

void Zombie::Init()
{
	m_speed = 100;
}

void Zombie::Update()
{
	m_curpos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	Movement();
	printf("Zombie (%f, %f)\n", m_curpos.x, m_curpos.y);
}

void Zombie::FinalUpdate()
{
}

void Zombie::Render()
{
}

void Zombie::Destroy()
{
}

void Zombie::Movement()
{
	m_curpos.x -= m_speed * fDT;

	gameObject->GetComponent<TransformComponent>()->SetPosition(m_curpos);
}
