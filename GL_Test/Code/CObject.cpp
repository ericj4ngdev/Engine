#include "include.h"

MemoryMgr* memoryMgr = nullptr;

CObject::CObject() {
    //memoryMgr = CORE->GetCore(MemoryMgr);

    // �޸� �ø���
}

CObject::~CObject() = default;

void CObject::Destroy() {
    memoryMgr->ReleaseObject(this);

}