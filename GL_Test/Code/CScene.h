#pragma once

class CScene
{
public:
    std::string m_name;
public:
	CScene();
	~CScene();

    virtual void Init() = 0;
    virtual void Enter() = 0;           // �ش� ���� ���Խ� ȣ��
    virtual void Exit() = 0;            // �ش� ���� Ż��� ȣ��
    virtual void Update() = 0;
    virtual void Destroy() = 0;

};

