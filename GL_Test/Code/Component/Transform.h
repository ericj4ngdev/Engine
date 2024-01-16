#pragma once
#include "CComponent.h"
#include "./Util/ITransform.h"

class Transform : public CComponent, public ITransform
{
private:
    mat4 m_f_matrix;
    vec3 m_f_position;
    vec3 m_f_scale;
    Quaternion m_f_rotation;

public:
    Transform();

    ~Transform() override;

    void Init() override;

    void Tick(float elapsedTime) override;

    void Exterminate();

    mat4 GetMatrix() const;

    vec3* GetPosition();

    vec3 GetScale() const;

private:
    // mat4 GetFinalMatrix() const;


};

