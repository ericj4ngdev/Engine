#include "include.h"

MemoryMgr* memoryMgr = nullptr;

CObject::CObject() {
    //memoryMgr = CORE->GetCore(MemoryMgr);

    // 메모리 올리기
}

CObject::~CObject() = default;

void CObject::Destroy() {
    memoryMgr->ReleaseObject(this);

}