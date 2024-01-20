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
    virtual void Enter() = 0;           // �ش� ���� ���Խ� ȣ��
    virtual void Exit() = 0;            // �ش� ���� Ż��� ȣ��
    void Tick();
    virtual void Destroy() = 0;
protected:
    inline void AddObject(CGameObject* pGameObject){ m_arrObj.push_back(pGameObject); }
};

