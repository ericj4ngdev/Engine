#pragma once
#include "Include.h"

class CGameObject;

class CComponent
{
public:
    CGameObject* gameObject = nullptr;
    bool bEnable = true;
    std::string m_classType;

public:
    CComponent() {};
    explicit CComponent(std::string classType, CGameObject* gameObject) : m_classType(std::move(classType)), gameObject(gameObject) {};
    CComponent(const CComponent& src) 
    {
        gameObject = src.gameObject;
        bEnable = src.bEnable;
        m_classType = src.m_classType;
    }
    virtual ~CComponent() = default;
    
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void FinalUpdate() = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;

    void SetGameObject(CGameObject* object) { gameObject = object; }
    virtual CGameObject* GetGameObject() const { return gameObject; }

    virtual bool GetIsEnable() const 
    {
        return bEnable;
    }
    virtual void SetIsEnable(bool is_enable)
    {
        bEnable = is_enable;
    }

    std::string GetClassType() const 
    {
        return m_classType;
    }

    void SetClassType(std::string type) 
    {
        m_classType = std::move(type);
    }
};