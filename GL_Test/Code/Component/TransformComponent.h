#pragma once

class TransformComponent : public CComponent, public ITransform
{
private:
    mat4 m_f_matrix;
    vec3 m_f_position;
    vec3 m_f_scale;
    Quaternion m_f_rotation;

public:
    explicit TransformComponent(CGameObject* l_gameObject);
    ~TransformComponent() override;

    void Init() override;

    void Tick() override;

    void Destroy() override;

    mat4 GetMatrix() const;

    vec3* GetPosition();

    vec3 GetScale() const;

private:
    // mat4 GetFinalMatrix() const;


};

