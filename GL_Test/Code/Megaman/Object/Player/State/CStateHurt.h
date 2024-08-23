#pragma once

class CStateHurt : public CStateBase
{
public:
	CStateHurt(CMegaman* Character);
	~CStateHurt() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:
	float m_fHitTimer;
};

