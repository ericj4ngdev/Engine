#pragma once

class CTexture;
class CRenderComponent : public CComponent
{
public:
	COMPONENT_DEFINE_CONSTRUCTOR(CRenderComponent)
	~CRenderComponent() override;
	void Init() override;
	void Tick() override;
	void Destroy() override;
	CTexture* GetTexture() { return m_texture; }
	void SetTexture(const char* name);
	void LoadPlaneVAO();
	void RenderPlaneVAO();
	void SetCenterPos(float x, float y);
	void SetScale(float x, float y);
private:
	CTexture* m_texture;
	int m_textureLayout = 0;
	GLuint m_Texid;
	GLuint programID;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_icenterPos;
	vec2 m_centerPos;
	vec2 m_Scale;
};

