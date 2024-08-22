#include "include.h"

CMegaman::CMegaman(string name) : CCharacter(name)
{

}

CMegaman::~CMegaman() = default;

void CMegaman::Init()
{
	
}

void CMegaman::Update()
{
	CCharacter::Update();
	
}

void CMegaman::OnCollisionEnter(CCollider* pOther)
{
}

void CMegaman::OnCollision(CCollider* pOther)
{
}

void CMegaman::OnCollisionExit(CCollider* pOther)
{
}

void CMegaman::Jump()
{
}

void CMegaman::TakeDamage(float damage, int dir)
{
}
