#pragma once
#include "EngineFramework/GameFramework/CGameObject.h"

enum class ENEMY_STATE
{
	IDLE,
	READY,
	MOVE,
	JUMP,
	FALL,
	ATTACK,
	HIT,
	DEAD,
};

class CEnemy : public CGameObject
{
public:
	CEnemy();
	explicit CEnemy(string name);
	virtual ~CEnemy();
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
protected:
	vec2 GetPlayerPosition();
	void ScreenOut();
	void SetDirection();
	virtual void UpdateState() = 0;
	void ChangeState(ENEMY_STATE newState);
public:
	virtual void TakeDamage() = 0;
protected:
	int m_iDir;
	int m_iHP;
	float m_fSpeed;
	float m_fDamage;
	ENEMY_STATE m_eCurState;
	
friend class CEnemySpawner;
};

