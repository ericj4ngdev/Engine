#pragma once
class SampleScene : public CScene
{
public:
	virtual void Init() override;
	virtual void Enter()override;
	virtual void Exit()override;
	virtual void Update() override;
	virtual void Destroy() override;
private:
	float startTIme = 0;
};

