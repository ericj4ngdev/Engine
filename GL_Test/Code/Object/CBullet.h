#pragma once
class CBullet : public CGameObject
{
public:
	CBullet();
	CBullet(string name);
	virtual ~CBullet();
	virtual void Init();
	virtual void Update();
	virtual void OnCollisionEnter(CCollider* pOther);
public:
};

