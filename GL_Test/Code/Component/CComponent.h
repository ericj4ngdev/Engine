#pragma once
#include "Include.h"

class CGameObject;

class CComponent
{
public:
    CGameObject* gameObject = nullptr;
    bool isEnable = true;
    std::string m_classType;

public :
    CComponent() {};
    CComponent(const CComponent& src) = default;
    virtual ~CComponent() = default;
    
    virtual void Start() = 0;

    virtual void Init() = 0;

    virtual void Tick(float elapsedTime) = 0;

    virtual void Destroy() = 0;
};