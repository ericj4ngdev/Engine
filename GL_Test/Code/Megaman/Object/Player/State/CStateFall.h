#pragma once

class CStateFall : public CStateBase
{
public:
	// �θ� Ŭ���� �����ڿ� "Jump" ����
	CStateFall(CMegaman* Character)
		: CStateBase(Character, "Fall") {}
	~CStateFall() override;

public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

