#pragma once

#include <string>

class CComponent;
class TransformComponent;

class CGameObject
{
public:
	CGameObject();
	explicit CGameObject(string name);
	virtual ~CGameObject() = default;

	virtual void Init() = 0;		// 순수가상함수
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();
public:
	// Component관련
	template <class T>
	T* GetComponent();
	template <class T>
	T* CreateComponent();
	void AddComponent(CComponent* component);
	void DeleteComponent(CComponent* component);
public:
	string GetName() const { return m_name; }
	void Setname(string name) { m_name = move(name); }
	bool GetIsEnable() const { return isEnable; }
	void SetIsEnable(bool is_enable);

protected:
	list<CGameObject*> m_children;
	list<CComponent*> m_components;
	string m_name;
	CGameObject* m_parent;
	TransformComponent* m_transform;
	bool isEnable;
protected:
	void UpdateComponent();
	void RenderComponent();

};

template<class T>
T* CGameObject::GetComponent()
{
	for(const auto& component : m_components)
	{
		if (component == nullptr) continue;
		// T 컴포넌트이면 T컴포넌트* 반환
		if (dynamic_cast<T*>(component)) {
			return static_cast<T*>(component);
		}
	}
	return nullptr;
}

template<class T>
T* CGameObject::CreateComponent()
{
	T* component = new T(this);
	AddComponent(component);
	component->Init();
	return component;
}
