#pragma once
class CScene : public CObject
{
public:
    std::string m_name;
public:
	CScene();
	~CScene() override;


    virtual void Init() = 0;
    virtual void Tick(float elapsedTime) = 0;
    void Destroy() override = 0;
    void Exterminate() override;



};

