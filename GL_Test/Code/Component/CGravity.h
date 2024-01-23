#pragma once
class CGravity : public CComponent
{
public:
	COMPONENT_DEFINE_CONSTRUCTOR(CGravity)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;
    ~CGravity();
private:
    bool m_bGround;
    float m_gravity;
public:
    void SetGround(bool b);
    void SetGravity(float grav) { m_gravity = grav; }
};

