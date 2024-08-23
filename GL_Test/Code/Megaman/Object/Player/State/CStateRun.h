#pragma once

class CStateRun : public CStateBase
{
public:
	CStateRun(CMegaman* Character)
		: CStateBase(Character, "Run") {}
	~CStateRun() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

