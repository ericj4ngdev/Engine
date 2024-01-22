#pragma once
#include "CComponent.h"
class Zombie :    public CComponent
{
public:
	Zombie(CGameObject* l_gameObject);
	~Zombie() override;
	void Init() override;
	void Update() override;
	void FinalUpdate() override;
	void Render() override;
	void Destroy() override;
public:
	void Movement();
private:
	vec2 m_curpos;
	float m_speed;
};

