#pragma once

class CRigidbody;

class ControllerComponent : public CComponent
{
public:
	ControllerComponent(CGameObject* l_gameObject);
	~ControllerComponent();
	void Init() override;
	void Update() override;
	void FinalUpdate() override;
	void Render() override;
	void Destroy() override;
	void Control();
	void SpecialAttack();
private:
	vec2 m_curpos;
	float m_speed;
	CRigidbody* m_rigidbody;
public:
	void SetSpeed(float sp) { m_speed = sp; }
};
