#pragma once

class ControllerComponent : public CComponent
{
public:
	COMPONENT_DEFINE_CONSTRUCTOR(ControllerComponent)
	~ControllerComponent();
	void Init();
	void Tick();
	void Destroy();
	void Control();
private:
	vec2 m_pos;
};

