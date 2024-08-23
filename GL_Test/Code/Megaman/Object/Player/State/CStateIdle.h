#pragma once

class CStateIdle : public CStateBase
{
public:
	CStateIdle(CMegaman* Character)
		: CStateBase(Character, "Idle") {}
	~CStateIdle() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

};

