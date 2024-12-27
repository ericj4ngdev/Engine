#pragma once
const int MAX_CONTROLLER = 8;
class CGameObject;
class CPlayerController;

class CScene
{
protected:
    vector<vector<std::unique_ptr<CGameObject>>> m_arrObj; // �׷캰�� ��ü ����
    vector<std::unique_ptr<CPlayerController>> m_arrPC;    // �÷��̾� ��Ʈ�ѷ� ����
    string m_name;

public:
	CScene();
	virtual ~CScene();
    void SetName(const std::string& strName) { m_name = strName; }
    const string GetName() { return m_name; }
    virtual void Init();
    virtual void Enter() = 0;           // �ش� ���� ���Խ� ȣ��
    virtual void Exit() = 0;            // �ش� ���� Ż��� ȣ��
    virtual void Update();  
    virtual void FinalUpdate();
    virtual void Render();
    virtual void Destroy() = 0;
public:
    void AddObject(std::unique_ptr<CGameObject> pGameObject, GROUP_TYPE eType);    
    const vector<std::unique_ptr<CGameObject>>& GetGroupObject(GROUP_TYPE eType) { return m_arrObj[(UINT)eType]; }
    void DeleteGroup(GROUP_TYPE eGroup);
    void DeleteAll();
    CPlayerController* GetController();
};

