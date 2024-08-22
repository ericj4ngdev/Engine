#pragma once

class CStateIdle : public CStateBase
{
public:
	CStateIdle(CCharacter* Character) : CStateBase(Character) {}
	~CStateIdle() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

};

