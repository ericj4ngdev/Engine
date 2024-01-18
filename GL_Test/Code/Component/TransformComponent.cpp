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

	/*if (GetKeyHold(W))
	{
		m_position.y += 1.f * fDT;
		printf("%f\n", m_position.y);
	}
	if (GetKeyHold(A))
	{
		m_position.x -= 1.f * fDT;
		printf("%f\n", m_position.x);
	}
	if (GetKeyHold(S))
	{
		m_position.y -= 1.f * fDT;
		printf("%f\n", m_position.y);
	}
	if (GetKeyHold(D))
	{
		m_position.x += 1.f * fDT;
		printf("%f\n", m_position.x);
	}*/
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
    printf("TransformComponent : m_position.y : %f / ", m_position.y);
}

vec3 TransformComponent::GetScale() const {
    return m_f_scale;
}

// mat4 Transform::GetFinalMatrix() const { return; }