#pragma once
#include "EngineFramework/GameFramework/CGameObject.h"
class CMap : public CGameObject
{
public:
	CMap(string name);
	virtual ~CMap();
	virtual void Init();
};

