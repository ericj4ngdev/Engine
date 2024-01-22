#include "include.h"


CGameObject::CGameObject() : m_parent(nullptr), isEnable(true)
{
    m_transform = CreateComponent<TransformComponent>();
}

CGameObject::CGameObject(std::string name) : m_parent(nullptr), isEnable(true)
{
    m_transform = CreateComponent<TransformComponent>();
}

void CGameObject::Update()
{
    if (!isEnable) return;
    UpdateComponent();
}

void CGameObject::FinalUpdate()
{
    if (!isEnable) return;
    for (const auto& component : m_components)
    {
        if (component == nullptr) continue;
        if (component->GetIsEnable())
            component->FinalUpdate();
    }
}

void CGameObject::Render()
{
    if (!isEnable) return;
    RenderComponent();
}

void CGameObject::Destroy()
{
    // 컴포넌트, 자식 모두 삭제
    auto iter = m_components.begin();
    while (iter != m_components.end())
    {
        auto component = *iter; // 첫 이터
        m_components.erase(iter++);
        if (component == nullptr) continue;
        // 메모리 해제 파트는 없음...
    }
    m_components.clear();
}

void CGameObject::AddComponent(CComponent* component)
{
    m_components.push_back(component);
}

void CGameObject::DeleteComponent(CComponent* component)
{
    m_components.remove(component);
}

void CGameObject::SetIsEnable(bool is_enable)
{
    for (const auto& component : m_components) 
    {
        if (component == nullptr) continue;
        component->SetIsEnable(is_enable);
    }
}

void CGameObject::UpdateComponent()
{
    for (const auto& component : m_components) 
    {
        if (component == nullptr) continue;
        if (component->GetIsEnable())
            component->Update();
    }
}

void CGameObject::RenderComponent()
{
    for (const auto& component : m_components)
    {
        if (component == nullptr) continue;
        if (component->GetIsEnable())
            component->Render();
    }
}
