#pragma once
#include "CGameObject.h"
class CBlock : public CGameObject
{
public:
	CBlock(string name);
	virtual ~CBlock();
	virtual void Init();
};

