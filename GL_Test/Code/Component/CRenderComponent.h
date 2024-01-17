#pragma once

class CTexture;
class CRenderComponent : public CComponent
{
public:
	explicit CRenderComponent();
	~CRenderComponent() override;
	void Init() override;
	void Tick() override;
	void Destroy() override;
	void SetTexture();
private:
	CTexture* m_texture;
	GLuint m_Texid;
	GLuint programID;
	GLuint VAO;
	GLuint VBO;
	float vertices[32] =
	{
		// 위치              // 컬러
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
	};
};

