#pragma once
#include "CComponent.h"

class CCollider : public CComponent
{
private:
    static UINT g_iNextID;
    vec2 m_offsetPos;
    vec2 m_pos;
    vec2 m_scale;
    UINT m_ID;      // 충돌체 고유 ID값
    int m_ColCount;
private:
    struct _SEdge {
        vec2	m_vLT;
        vec2	m_vRT;
        vec2	m_vRB;
        vec2	m_vLB;
    };
    typedef struct _SEdge SEdge;
    SEdge   m_struEdge;
    vec2    m_vCurColPos;
    vec2    m_vPrevColPos;
    vec2    m_vDirection;
public:
    vec2 GetOffsetPos() const { return m_offsetPos; }
    vec2 GetPos() const{ return m_pos; }
    vec2 GetScale() const { return m_scale; }
    UINT GetID() const { return m_ID; }
    vec2 GetDirection() const { return m_vDirection; }
    SEdge GetEdges() const { return m_struEdge; }
    void SetOffsetPos(vec2 pos) { m_offsetPos = pos; }
    void SetScale(vec2 scale) { m_scale = scale; }    
public:
    COMPONENT_DEFINE_CONSTRUCTOR(CCollider)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;
    void DrawRectangle(vec2 scale, Color4f color);
public:
    void OnCollision(CCollider* pOther);        // 충돌중인 경우 호출 함수
    void OnCollisionEnter(CCollider* pOther);   // 충돌 시작
    void OnCollisionExit(CCollider* pOther);    // 충돌 해제
public:
    CCollider(const CCollider& _origin);
    CCollider& operator = (CCollider& _origin) = delete;    // 대입연산 삭제
    ~CCollider();
};

