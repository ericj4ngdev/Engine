#pragma once
class CComponent;
class TransformComponent;

class CGameObject
{
public:
	CGameObject();
	explicit CGameObject(string name);
	virtual ~CGameObject();

	virtual void Init();		// ���������Լ�
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();
public:
	// Component����
	template <class T>
	T* GetComponent();
	template <class T>
	T* CreateComponent();
	void AddComponent(CComponent* component);
	void DeleteComponent(CComponent* component);
public:
	string GetName() const { return m_name; }
	void Setname(const string name) { m_name = move(name); }
	bool GetIsEnable() const { return m_bEnable; }
	void SetIsEnable(bool is_enable);
	vec2 GetPos() { return m_transform->GetPosition(); }
	vec2 GetScale() { return m_transform->GetScale(); }
	void SetPos(vec2 v) { m_transform->SetPosition(v); }	// ���� �Ἥ ������ 
	void SetScale(vec2 v) { m_transform->SetScale(v); }
	bool IsDead() {	return !m_bAlive; }
	void SetDead() { m_bAlive = false; }		// �̺�Ʈ �Ŵ��� �뵵
	vec2 GetRenderPos() {return m_vRenderPos;}
	virtual void OnCollision(CCollider* pOther){}
	virtual void OnCollisionEnter(CCollider* pOther){}
	virtual void OnCollisionExit(CCollider* pOther){}
protected:
	TransformComponent* m_transform;
	vec2 m_vRenderPos;
	list<CGameObject*> m_children;
	list<CComponent*> m_components;
	string m_name;
	CGameObject* m_parent;
	bool m_bEnable;
	bool m_bAlive;
protected:
	void InitComponent();
	void UpdateComponent();
	void RenderComponent();
};

template<class T>
T* CGameObject::GetComponent()
{
	for(const auto& component : m_components)
	{
		if (component == nullptr) continue;
		// T ������Ʈ�̸� T������Ʈ* ��ȯ
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
	// component->Init();
	return component;
}
