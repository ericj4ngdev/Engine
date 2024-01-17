#include "include.h"

CRenderComponent::CRenderComponent(CGameObject* l_gameObject) : CComponent("CRenderComponent", l_gameObject) {
	m_VAO = 0;
	m_VBO = 0;
	programID = 0;
	programID = ShaderUtil::CreateProgram("VertexShader.txt", "FragmentShader.txt");
	LoadPlaneVAO();
}

CRenderComponent::~CRenderComponent()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void CRenderComponent::Init()
{
	
}

void CRenderComponent::Tick()
{
	// 그리기
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programID);
	RenderPlaneVAO();
	glutSwapBuffers();
}

void CRenderComponent::Destroy()
{
}

void CRenderComponent::SetTexture(const char* name)
{
	if (m_texture == nullptr) {
		m_texture = new CTexture();
	}
	m_texture->LoadImage(name);
	m_Texid = NULL;
	m_Texid = *m_texture->GetTexture();
	// Bind까지 함
	// m_texture->Bind();
}

void CRenderComponent::LoadPlaneVAO()
{
	float vertices[32] =
	{
		// 위치              // 컬러
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);     // 1. Vertex Array Object 바인딩

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void CRenderComponent::RenderPlaneVAO()
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);
}
