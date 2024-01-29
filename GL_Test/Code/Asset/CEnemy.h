#pragma once
#include "CGameObject.h"
class CEnemy : public CGameObject
{
public:
	CEnemy(string name);
	~CEnemy();
	void Init();
	virtual void Update();
	virtual void OnCollisionEnter(CCollider* pOther);

public:
	vec2 m_curpos;
	float m_fSpeed;
};

