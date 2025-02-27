#pragma once
#include "EngineFramework/GameFramework/CGameObject.h"

class CPlayer : public CGameObject
{
public:
	CPlayer(string name);
	virtual ~CPlayer();
	virtual void Init();
	virtual void Update();
	// virtual void FinalUpdate() override;
	// virtual void Render() override;
	// virtual void Destroy() override;

	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
public:
	void TakeDamage(float damage, int dir);
private:
	int m_StepedBlockCount;

	
};

