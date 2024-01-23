#pragma once
#include "CComponent.h"
class CRigidbody : public CComponent
{
public:
	COMPONENT_DEFINE_CONSTRUCTOR(CRigidbody)
public:
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;
    ~CRigidbody();
private:
    vec2 m_vForce;
    vec2 m_vAccel;
    vec2 m_vVelocity;
    float m_fMaxSpeed;
    float m_fFricCoeff;     // Friction Coefficient
    float m_Mass;
    float m_speed;
public:
    void AddForce(vec2 vforce) { m_vForce += vforce; }
    void SetMass(float mass) { m_Mass = mass; }
    float GetMass() { return m_Mass; }
    void SetVelocity(vec2 v) { m_vVelocity = v; }
    void SetMaxSpeed(float v) { m_fMaxSpeed = v; }
    vec2 GetVelocity() { return m_vVelocity; }
    void Move();
};

