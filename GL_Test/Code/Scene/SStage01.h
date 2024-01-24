#pragma once
#include "CScene.h"
class SStage01 : public CScene
{
public:
	virtual void Init() override;
	virtual void Enter()override;
	virtual void Exit()override;
	virtual void Update() override;
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy() override;
public:
	SStage01();
	virtual ~SStage01();
};

