#pragma once
class CStateBase
{
public:
	CStateBase(CMegaman* Character, const string& name)
		: m_Character(Character), m_Name(name) {}
	virtual ~CStateBase();

public:
	virtual void Enter() {}
	virtual void Update(){}
	virtual void Exit(){}

public:
	virtual const string& GetName() const { return m_Name; }

protected:
	CMegaman* m_Character;
	string m_Name;
};

