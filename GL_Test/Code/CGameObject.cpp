#include "include.h"


CGameObject::CGameObject() {
    
}

CGameObject::~CGameObject() = default;

void CGameObject::Init() {
    m_parent = nullptr;
    isEnable = true;
    m_isPrefab = false;
}

void CGameObject::Tick(float elapsedTime) {
    if (!isEnable) return;
    // UpdateComponent(elapsedTime);
}

void CGameObject::Destroy() {

}