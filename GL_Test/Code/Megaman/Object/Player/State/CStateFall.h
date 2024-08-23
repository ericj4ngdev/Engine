#pragma once

class CStateFall : public CStateBase
{
public:
	// 부모 클래스 생성자에 "Jump" 전달
	CStateFall(CMegaman* Character)
		: CStateBase(Character, "Fall") {}
	~CStateFall() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

