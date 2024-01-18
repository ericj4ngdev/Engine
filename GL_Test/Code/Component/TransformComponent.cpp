#include "Include.h"

COMPONENT_CONSTRUCTOR(TransformComponent) 
{
    m_position = vec3(0, 0, 0);
    m_rotation = Quaternion();
    m_scale = vec3(1, 1, 1);
}

TransformComponent::~TransformComponent() = default;

void TransformComponent::Init() {
}

void TransformComponent::Tick() {
	gameObject->GetComponent<CRenderComponent>()->SetCenterPos(m_position.x, m_position.y);
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


void TransformComponent::SetPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
    // printf("TransformComponent : m_position.y : %f / ", m_position.y);
}

vec3 TransformComponent::GetScale() const {
    return m_f_scale;
}

// mat4 Transform::GetFinalMatrix() const { return; }