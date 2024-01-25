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
    vec2 m_vAccelA;         // 추가 가속도
    vec2 m_fMaxVelocity;
    float m_fFricCoeff;     // Friction Coefficient
    float m_Mass;
    float m_speed;
public:
    void AddForce(vec2 vforce) { m_vForce += vforce; }
    void AddVelocity(vec2 v) { m_vVelocity += v; }
    
    void SetMass(float mass) { m_Mass = mass; }
    void SetFriction(float friction) { m_fFricCoeff = friction; }
    void SetVelocity(vec2 v) { m_vVelocity = v; }
    void SetMaxVelocity(vec2 v) { m_fMaxVelocity = v; }
    void SetAccelAlpha(vec2 vAccel) { m_vAccelA = vAccel; }

    float GetMass() { return m_Mass; }
    vec2 GetVelocity() { return m_vVelocity; }
    float GetSpeed() { return m_vVelocity.Length(); }

    void Move();
};

