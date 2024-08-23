#include "include.h"

COMPONENT_CONSTRUCTOR(CStatComponent)
{
	m_MaxHP = 100;
	m_Life = 1;
	m_CurrentHP = m_MaxHP;
}

CStatComponent::~CStatComponent()
{
}

void CStatComponent::Init()
{
}

void CStatComponent::Update()
{
	
}

void CStatComponent::FinalUpdate()
{
}

void CStatComponent::Render()
{
}

void CStatComponent::Destroy()
{
}

void CStatComponent::TakeDamage(float damage, int dir)
{
	CMegaman* Character = dynamic_cast<CMegaman*>(gameObject);
	
	printf("Damaged!");
	if (DecreaseHP(damage))
	{
		Character->KnockBack(dir);
	}
	else
	{
		// ChangeState(PLAYER_STATE::DEAD);
	}
	
}

bool CStatComponent::DecreaseHP(float damage)
{
	m_CurrentHP -= damage;
	if (m_CurrentHP <= 0)
	{
		m_CurrentHP = 0;
		return false;
	}
	else
	{
		return true;
	}
	return false;
}
