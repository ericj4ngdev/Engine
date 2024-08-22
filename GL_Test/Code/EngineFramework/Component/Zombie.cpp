#include "include.h"


Zombie::Zombie(CGameObject* l_gameObject) : CComponent("Zombie", l_gameObject)
{
	
}

Zombie::~Zombie()
{
}

void Zombie::Init()
{
}

void Zombie::Update()
{
	
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
