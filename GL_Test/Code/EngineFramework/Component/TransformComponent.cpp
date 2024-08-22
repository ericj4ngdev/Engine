#include "Include.h"

TransformComponent::TransformComponent(CGameObject* l_gameObject) : CComponent("TransformComponent", l_gameObject)
{
    m_position = vec2(0, 0);
    m_scale = vec2(1, 1);
}

TransformComponent::~TransformComponent() = default;

void TransformComponent::Init() 
{

}

void TransformComponent::Update() 
{

}

void TransformComponent::FinalUpdate()
{

}

void TransformComponent::Render()
{

}

void TransformComponent::Destroy()
{

}

void TransformComponent::SetPosition(vec2 v)
{
    m_position.x = v.x;
    m_position.y = v.y;
}

void TransformComponent::SetScale(vec2 v) {
    m_scale.x = v.x;
    m_scale.y = v.y;
}