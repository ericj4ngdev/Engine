#pragma once
class CSword : public CGameObject
{
public:
	CSword();
	CSword(string name);
	virtual ~CSword();
	virtual void Init();
	virtual void OnCollisionEnter(CCollider* pOther);
public:
};

