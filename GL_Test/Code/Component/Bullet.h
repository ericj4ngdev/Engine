#pragma once

class Bullet : public CComponent
{
public:
    COMPONENT_DEFINE_CONSTRUCTOR(Bullet)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;
    ~Bullet();
public:
    void Movement();
    void SetDir(vec2 v) { m_vDirection = v.Normalize(); }
private:
    vec2 m_curpos;
    vec2 m_vDirection;
    float m_speed;
};

