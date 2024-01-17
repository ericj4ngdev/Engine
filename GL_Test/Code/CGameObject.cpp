#include "include.h"


CGameObject::CGameObject() {
    
}

CGameObject::CGameObject(std::string name)
{
}

CGameObject::~CGameObject() = default;

void CGameObject::Init() {
    m_parent = nullptr;
    isEnable = true;
}

void CGameObject::Tick(float elapsedTime) {
    if (!isEnable) return;



}

void CGameObject::Destroy()
{

}

void CGameObject::AddComponent(CComponent* component)
{
}

void CGameObject::DeleteComponent(CComponent* component)
{
}

void CGameObject::AddChild(CGameObject* object)
{
}

void CGameObject::RemoveChild(CGameObject* object)
{
}

CGameObject* CGameObject::GetParent()
{
    return nullptr;
}

void CGameObject::SetParent(CGameObject* object)
{
}

void CGameObject::RemoveParent()
{
}

void CGameObject::SetIsEnable(bool is_enable)
{
    for (const auto& component : m_Components) 
    {
        if (component == nullptr) continue;
        component->SetIsEnable(is_enable);
    }
}

void CGameObject::UpdateComponent(float elapsedTime)
{
    for (const auto& component : m_Components) 
    {
        if (component == nullptr) continue;
        if (component->GetIsEnable())
            component->Tick(elapsedTime);
    }
}
