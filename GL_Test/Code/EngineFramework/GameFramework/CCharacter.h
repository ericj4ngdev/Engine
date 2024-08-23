#pragma once
#include "EngineFramework/GameFramework/CGameObject.h"

class CCharacter : public CGameObject
{
public:
	CCharacter(string name);
	virtual ~CCharacter();
	virtual void Init();
	virtual void Update();
	// virtual void FinalUpdate() override;
	// virtual void Render() override;
	// virtual void Destroy() override;

public:
	virtual void Possessedby(CPlayerController* InController);
	virtual void UnPossesed();
	
	CPlayerController* GetController() const { return m_Controller; }
	virtual void Jump();
	virtual void TakeDamage(float damage, int dir);
	bool GetbDamaged() { return m_bDamaged; }
	void SetbDamaged(bool InDamaged) { m_bDamaged = InDamaged; }
public:
	UINT8 bOnAir : 1;
protected:
	CPlayerController* m_Controller;	
	CStateBase* m_CurrentState;
	bool m_bDamaged;
};

