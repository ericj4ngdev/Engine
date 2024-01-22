#pragma once

class TransformComponent : public CComponent
{
public:
    TransformComponent(CGameObject* l_gameObject);
    ~TransformComponent() override;

    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;

    vec2 GetPosition() const { return m_position; }
    void SetPosition(vec2 v);
    vec2 GetScale() const{ return m_scale; }
    void SetScale(vec2 v);
private:
    vec2 m_position;
    Quaternion m_rotation;
    vec2 m_scale;
};

