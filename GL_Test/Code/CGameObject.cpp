#include "include.h"


CGameObject::CGameObject() 
{
    m_transform = CreateComponent<Transform>();
    CGameObject::Init();
}

CGameObject::CGameObject(std::string name)
{
    m_transform = CreateComponent<Transform>();
    m_name = std::move(name);
    CGameObject::Init();
}

CGameObject::~CGameObject() = default;

void CGameObject::Init()
{
    // 추가
    m_parent = nullptr;
    isEnable = true;
}

void CGameObject::Tick(float elapsedTime) 
{
    if (!isEnable) return;
    UpdateComponent(elapsedTime);
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

    if (m_parent != NULL) RemoveParent();

    {
        auto iter = m_children.begin();
        while (iter != m_children.end())
        {
            auto object = *iter; // 첫 이터
            m_children.erase(iter++);
            if (object == nullptr) continue;
            object->Destroy();
            // 메모리 해제 파트는 없음...
        }
    }
    // m_status = DESTROY;

}

void CGameObject::AddComponent(CComponent* component)
{
    auto str_class = component->GetClassType();
    m_components.push_back(component);
}

void CGameObject::DeleteComponent(CComponent* component)
{
    m_components.remove(component);
}

void CGameObject::AddChild(CGameObject* object)
{
    // 부모입장에서 object는 자식
    if (object == NULL) return;
    object->RemoveParent();
    m_children.push_back(object);
    object->m_parent = this;
}

void CGameObject::RemoveChild(CGameObject* object)
{
    if (object == nullptr) return;
    m_children.remove(object);
    object->m_parent = nullptr;
}

CGameObject* CGameObject::GetParent()
{    
    return m_parent;
}

void CGameObject::SetParent(CGameObject* object)
{
    object->AddChild(this);
}

void CGameObject::RemoveParent()
{
    if (m_parent != NULL) return;
    m_parent->RemoveChild(this);    
}

const std::list<CGameObject*>& CGameObject::GetChildren() const
{
    return m_children;
}

void CGameObject::SetIsEnable(bool is_enable)
{
    for (const auto& component : m_components) 
    {
        if (component == nullptr) continue;
        component->SetIsEnable(is_enable);
    }
}

void CGameObject::UpdateComponent(float elapsedTime)
{
    for (const auto& component : m_components) 
    {
        if (component == nullptr) continue;
        if (component->GetIsEnable())
            component->Tick(elapsedTime);
    }
}
