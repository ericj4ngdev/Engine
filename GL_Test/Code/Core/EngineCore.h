#pragma once
#include "Cmacro.h"
class EngineCore
{
	SINGLE(EngineCore)

public:
	void Init();
	void Update();
	void Render();
	void Event();
};


