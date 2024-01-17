#include "include.h"

CRenderComponent::CRenderComponent()
{
	VAO = 0;
	VBO = 0;
	programID = 0;
}

CRenderComponent::~CRenderComponent()
{
	glDeleteVertexArrays(1, &VAO);
}

void CRenderComponent::Init()
{
	m_texture->LoadImage("Code/Asset/Image/Test.png");
	m_Texid = NULL;
	m_Texid = *(m_texture->GetTexture());
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);     // 1. Vertex Array Object 바인딩

	programID = ShaderUtil::CreateProgram("VertexShader.txt", "FragmentShader.txt");
}

void CRenderComponent::Tick()
{
	// 그리기
	// bind Texture
	glBindTexture(GL_TEXTURE_2D, m_Texid);

	glUseProgram(programID);
	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 4);


	glBindVertexArray(VAO);     // 1. Vertex Array Object 바인딩    

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void CRenderComponent::Destroy()
{
}

void CRenderComponent::SetTexture()
{
}
