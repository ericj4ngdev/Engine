#pragma once
#include "CComponent.h"
class CCollider : public CComponent
{
private:
    static UINT g_iNextID;
    vec2 m_offsetPos;
    vec2 m_pos;
    vec2 m_scale;
    UINT m_ID;      // �浹ü ���� ID��
public:
    vec2 GetOffsetPos() { return m_offsetPos; }
    vec2 GetPos() { return m_pos; }
    vec2 GetScale() { return m_scale; }
    void SetOffsetPos(vec2 pos) { m_offsetPos = pos; }
    void SetScale(vec2 scale) { m_scale = scale; }
    UINT GetID() { return m_ID; }
public:
    COMPONENT_DEFINE_CONSTRUCTOR(CCollider)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void DrawRectangle(vec2 scale, Color4f color);
    void Destroy() override;
public:
    void OnCollision(CCollider* pOther);        // �浹���� ��� ȣ�� �Լ�
    void OnCollisionEnter(CCollider* pOther);   // �浹 ����
    void OnCollisionExit(CCollider* pOther);    // �浹 ����
public:
    CCollider(const CCollider& _origin);
    CCollider& operator = (CCollider& _origin) = delete;    // ���Կ��� ����
    ~CCollider();
};

