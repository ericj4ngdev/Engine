#pragma once

class CGameObject;

class CScene
{
protected:
    vector<CGameObject*> m_arrObj[(UINT)GROUP_TYPE::END];
    string m_name;

public:
	CScene();
	virtual ~CScene();
    void SetName(const std::string& strName) { m_name = strName; }
    const string GetName() { return m_name; }
    virtual void Init() = 0;
    virtual void Enter() = 0;           // 해당 씬에 진입시 호출
    virtual void Exit() = 0;            // 해당 씬에 탈출시 호출
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render();
    virtual void Destroy() = 0;
public:
    void AddObject(CGameObject* pGameObject, GROUP_TYPE eType){ m_arrObj[(UINT)eType].push_back(pGameObject); }
    const vector<CGameObject*>& GetGroupObject(GROUP_TYPE eType) { return m_arrObj[(UINT)eType]; }
    void DeleteGroup(GROUP_TYPE eGroup);
    void DeleteAll();
};

