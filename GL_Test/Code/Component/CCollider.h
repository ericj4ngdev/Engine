#pragma once
#include "CComponent.h"
class CCollider : public CComponent
{
private:
    vec2 m_offsetPos;
    vec2 m_pos;
    vec2 m_scale;

public:
    vec2 GetOffsetPos() { return m_offsetPos; }
    vec2 GetScale() { return m_scale; }
    void SetOffsetPos(vec2 pos) { m_offsetPos = pos; }
    void SetScale(vec2 scale) { m_scale = scale; }

public:
    COMPONENT_DEFINE_CONSTRUCTOR(CCollider)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void DrawRectangle(float width, float height, const Vector4<GLfloat>& color);
    void Destroy() override;
public:
    CCollider();
    ~CCollider();

};

