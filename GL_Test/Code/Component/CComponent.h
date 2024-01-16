#pragma once
#include <string>
#include <map>
#include "IComponent.h"
#include "CObject.h"

class CGameObject;

class CComponent : public CObject, public IComponent {
protected:
    CGameObject* gameObject = nullptr;
    bool isEnable = true;

    std::string m_classType;
public :
    CComponent() {};

    explicit CComponent(std::string classType, CGameObject* gameObject) : m_classType(std::move(classType)),
        gameObject(gameObject) {
    }
    CComponent(const CComponent& src) : IComponent(src) {
        gameObject = src.gameObject;
        isEnable = src.isEnable;
        m_classType = src.m_classType;
    }
    ~CComponent() override = default;


    void Enter() override {}

    virtual CComponent* Clone(CGameObject* object) {
        return nullptr;
    }

    virtual void CopyReference(CComponent* src, std::map<CGameObject*, CGameObject*> lists_obj,
        std::map<CComponent*, CComponent*> lists_comp) {}

    virtual auto GetComponent() -> CObject* {
        return this;
    }


    void SetGameObject(CGameObject* object) { gameObject = object; }

    virtual CGameObject* GetGameObject() const { return gameObject; }
    virtual bool GetIsEnable() const { return isEnable; }
    virtual void SetIsEnable(bool is_enable) { isEnable = is_enable; }
    std::string GetClassType() const { return m_classType; }
    void SetClassType(std::string type) { m_classType = std::move(type); }
};