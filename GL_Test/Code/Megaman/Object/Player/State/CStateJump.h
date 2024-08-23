#pragma once

class CStateJump : public CStateBase
{
public:
	// 부모 클래스 생성자에 "Jump" 전달
	CStateJump(CMegaman* Character)
		: CStateBase(Character, "Jump") {}
	~CStateJump() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

