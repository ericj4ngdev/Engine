#pragma once

class Sword : public CComponent
{
public:
    COMPONENT_DEFINE_CONSTRUCTOR(Sword)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;
    ~Sword();
public:
    void Movement();
    void SetDir(vec2 v) { m_vDirection = v.Normalize(); }
private:
    vec2 m_curpos;
    vec2 m_vDirection;
    float m_speed;
};

