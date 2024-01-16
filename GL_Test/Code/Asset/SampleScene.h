#pragma once
class SampleScene : public CScene
{

	virtual void Init();
	virtual void Enter();
	virtual void Exit();
	virtual void Tick(float elapsedTime);
	virtual void Update();
	virtual void Destroy();
};

