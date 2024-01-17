#include "Include.h"

TransformComponent::TransformComponent(CGameObject* l_gameObject) : CComponent("Transform", l_gameObject) {
    m_position = vec3(0, 0, 0);
    m_rotation = Quaternion();
    m_scale = vec3(1, 1, 1);
}

TransformComponent::~TransformComponent() = default;

void TransformComponent::Init() {
}

void TransformComponent::Tick() {

    //m_f_matrix = GetFinalMatrix();
    m_f_position = vec3(m_f_matrix.w.x, m_f_matrix.w.y, m_f_matrix.w.z );
    m_f_scale = vec3(m_f_matrix.x.x, m_f_matrix.y.y, m_f_matrix.z.z );

}

void TransformComponent::Destroy()
{
}


mat4 TransformComponent::GetMatrix() const {
    return m_f_matrix;
}

vec3* TransformComponent::GetPosition() {
    return &m_f_position;
}

vec3 TransformComponent::GetScale() const {
    return m_f_scale;
}

// mat4 Transform::GetFinalMatrix() const { return; }