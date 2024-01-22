#pragma once

class CTexture;
class CRenderComponent : public CComponent
{
public:
	CRenderComponent(CGameObject* l_gameObject);
	~CRenderComponent() override;
	void Init() override;
	void Update() override;
	void FinalUpdate() override;
	void Render() override;
	void Destroy() override;
public:
	CTexture* GetTexture() { return m_texture; }
	void SetTexture(const string& _strKey, const char* name);
	void RenderPlaneVAO();
	void SetCenterPos(float x, float y);
	void SetScale(float x, float y);
private:
	CTexture* m_texture;
	GLuint m_Texid;
	vec2 m_centerPos;
	vec2 m_Scale;
	Color4f m_color;
};

