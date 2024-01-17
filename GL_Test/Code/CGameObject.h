#pragma once

#include <string>

class CComponent;
struct ITransform;

class CGameObject : public CObject
{
public:
	CGameObject();
	explicit CGameObject(std::string name);
	~CGameObject() override;

	virtual void Init();
	virtual void Tick(float elapsedTime);
	void Destroy() override;
public:
	// Component관련
	template <class T>
	T* GetComponent();
	template <class T>
	T* CreateComponent();
	void AddComponent(CComponent* component);
	void DeleteComponent(CComponent* component);
public:
	// Object관련
	void AddChild(CGameObject* object);
	void RemoveChild(CGameObject* object);
	CGameObject* GetParent();
	void SetParent(CGameObject* object);
	void RemoveParent();
	const std::list<CGameObject*>& GetChildren() const;
public:
	std::string GetName() const { return m_name; }
	void Setname(std::string name) { m_name = std::move(name); }
	ITransform* GetTransform() const { return m_transform; }
	bool GetIsEnable() const { return isEnable; }
	void SetIsEnable(bool is_enable);

private:
	std::list<CGameObject*> m_children;
	std::list<CComponent*> m_components;
	std::string m_name;
	ITransform* m_transform;
	CGameObject* m_parent;

	bool isEnable;
private:
	void UpdateComponent(float elapsedTime);

};

template<class T>
T* CGameObject::GetComponent()
{
	for(const auto& component : m_components)
	{
		if (component == nullptr) continue;
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
