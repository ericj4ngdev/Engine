#pragma once

class CStateJump : public CStateBase
{
public:
	// �θ� Ŭ���� �����ڿ� "Jump" ����
	CStateJump(CMegaman* Character)
		: CStateBase(Character, "Jump") {}
	~CStateJump() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

