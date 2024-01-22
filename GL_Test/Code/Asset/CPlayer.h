#pragma once
#include "CGameObject.h"
class CPlayer : public CGameObject
{
public:
	CPlayer(string name);
	virtual ~CPlayer();
	virtual void Init();
	// virtual void Update() override;
	// virtual void FinalUpdate() override;
	// virtual void Render() override;
	// virtual void Destroy() override;
private:
	vec2 pos;

	
};

