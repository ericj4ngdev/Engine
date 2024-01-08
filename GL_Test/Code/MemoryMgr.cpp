#include "include.h"

MemoryMgr::MemoryMgr() = default;
MemoryMgr::~MemoryMgr() = default;

void MemoryMgr::Init() {

}

void MemoryMgr::ExterminateObjects(bool KillAll = false) {

}

void MemoryMgr::ReleaseObject(CObject* object, bool isForce = false) {
    if (object == nullptr) return;

    if (object->isUndestroyable && !isForce) {
        OutputDebugStringA("Releasing Object is denied.");
        return;
    }

}