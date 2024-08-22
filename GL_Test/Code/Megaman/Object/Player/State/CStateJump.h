#pragma once

class CStateJump : public CStateBase
{
public:
	CStateJump(CCharacter* Character) : CStateBase(Character) {}
	~CStateJump() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

