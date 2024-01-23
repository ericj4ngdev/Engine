#pragma once
#include "CGameObject.h"
class CBlock : public CGameObject
{
public:
	CBlock(string name);
	virtual ~CBlock();
	virtual void Init();

	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
private:
	int count = 0;
public:
	void SetCount(int c) { count = c; }

};

