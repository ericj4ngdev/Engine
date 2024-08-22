#pragma once

class CStateRun : public CStateBase
{
public:
	CStateRun(CCharacter* Character) : CStateBase(Character) {}
	~CStateRun() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

