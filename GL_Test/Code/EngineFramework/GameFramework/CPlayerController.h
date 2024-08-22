#pragma once
#include "EngineFramework/GameFramework/CGameObject.h"
class CCharacter;
class CStateBase;
class FSM;
class CStateIdle;
class CStateJump;

class CPlayerController : public CGameObject
{
public:
	CPlayerController(string name);

	virtual ~CPlayerController();
	
	virtual void Init() override;
	virtual void Update() override;
public:
	virtual void OnPossess(CCharacter* InCharacter);
	virtual void OnUnPossess() final;
	virtual void SetCharacter(CCharacter* InCharacter);
	virtual CCharacter* GetCharacter() { return m_Character; }

protected:
	CCharacter* m_Character;
};

