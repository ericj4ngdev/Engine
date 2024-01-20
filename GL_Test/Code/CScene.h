#pragma once

class CGameObject;

class CScene
{
protected:
    std::vector<CGameObject*> m_arrObj;
    std::string m_name;

public:
	CScene();
	virtual ~CScene();
    void SetName(const std::string& _strName) { m_name = _strName; }
    virtual void Init() = 0;
    virtual void Enter() = 0;           // 해당 씬에 진입시 호출
    virtual void Exit() = 0;            // 해당 씬에 탈출시 호출
    void Tick();
    virtual void Destroy() = 0;
protected:
    inline void AddObject(CGameObject* pGameObject){ m_arrObj.push_back(pGameObject); }
};

