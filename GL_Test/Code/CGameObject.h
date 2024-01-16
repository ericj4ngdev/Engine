#pragma once

#include <string>

class CComponent;

class CGameObject : public CObject
{
private:
	std::list<CGameObject*> m_children;
	CGameObject* m_parent;

	std::string m_name;
	bool isEnable;
	bool m_isPrefab;

public:
	CGameObject();
	~CGameObject() override;

	virtual void Init();
	virtual void Tick(float elapsedTime);
	void Destroy() override;



};

