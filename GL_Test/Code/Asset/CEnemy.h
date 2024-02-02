#pragma once
#include "CGameObject.h"

class CEnemy : public CGameObject
{
public:
	CEnemy();
	explicit CEnemy(string name);
	virtual ~CEnemy();
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(CCollider* pOther);
protected:
	vec2 GetPlayerPosition();
	void ScreenOut();
	void SetDirection();
protected:
	int m_iDir;
	int m_iHP;
	float m_fSpeed;
	float m_fDamage;
	
friend class CEnemySpawner;
};

