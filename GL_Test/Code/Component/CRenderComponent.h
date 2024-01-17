#pragma once

class CTexture;
class CRenderComponent : public CComponent
{
public:
	explicit CRenderComponent(CGameObject* l_gameObject);
	~CRenderComponent() override;
	void Init() override;
	void Tick() override;
	void Destroy() override;
	void SetTexture(const char* name);
	void LoadPlaneVAO();
	void RenderPlaneVAO();
private:
	CTexture* m_texture;
	int m_textureLayout = 0;
	GLuint m_Texid;
	GLuint programID;
	GLuint m_VAO;
	GLuint m_VBO;
	
};

