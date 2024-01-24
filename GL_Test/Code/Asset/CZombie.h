#pragma once
#include "CGameObject.h"
class CZombie : public CGameObject
{
public:
	CZombie(string name);
	~CZombie();
	void Init();
	virtual void OnCollisionEnter(CCollider* pOther);
};

