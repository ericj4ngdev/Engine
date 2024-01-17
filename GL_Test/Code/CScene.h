#pragma once

class CScene
{
public:
    std::string m_name;
public:
	CScene();
	~CScene();

    virtual void Init() = 0;
    virtual void Enter() = 0;           // 해당 씬에 진입시 호출
    virtual void Exit() = 0;            // 해당 씬에 탈출시 호출
    virtual void Update() = 0;
    virtual void Destroy() = 0;

};

