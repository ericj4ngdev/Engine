#pragma once
class CStateBase
{
public:
	CStateBase(CCharacter* Character) : m_Character(Character) {}
	virtual ~CStateBase();

public:
	virtual void Enter() {}
	virtual void Update(){}
	virtual void Exit(){}

protected:
	CCharacter* m_Character;
};

