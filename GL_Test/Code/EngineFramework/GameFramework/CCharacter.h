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
	FSM* GetFSM() const { return m_FSM; }
	void SetFSM(FSM* PlayerFSM) { m_FSM = PlayerFSM; }
public:
	UINT8 bOnAir : 1;
protected:
	CPlayerController* m_Controller;
	FSM* m_FSM;
	CStateBase* m_CurrentState;
};

