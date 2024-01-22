#include "include.h"

CRenderComponent::CRenderComponent(CGameObject* l_gameObject) : CComponent("CRenderComponent", l_gameObject)
{
	m_VAO = 0;
	m_VBO = 0;
	programID = 0;
	std::string strFilePath_vert = CPathMgr::GetInstance()->GetContentPath();
	std::string strFilePath_frag = CPathMgr::GetInstance()->GetContentPath();
	strFilePath_vert += "shader\\VertexShader.txt";
	strFilePath_frag += "shader\\FragmentShader.txt";
	
	programID = ShaderUtil::CreateProgram(strFilePath_vert.c_str(), strFilePath_frag.c_str());
	LoadPlaneVAO();
}

CRenderComponent::~CRenderComponent()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void CRenderComponent::Init()
{
	
}

void CRenderComponent::Update()
{
	vec2 vObjectPos = gameObject->GetComponent<TransformComponent>()->GetPosition();
	SetCenterPos(vObjectPos.x, vObjectPos.y);

	vec2 vObjectScale = gameObject->GetComponent<TransformComponent>()->GetScale();
	SetScale(vObjectScale.x, vObjectScale.y);
}

void CRenderComponent::FinalUpdate()
{
}

void CRenderComponent::Render()
{
	// 그리기	
	glUseProgram(programID);
	RenderPlaneVAO();
	// 위치
	m_iCenterPos = glGetUniformLocation(programID, "movePos");
	glUniform3f(m_iCenterPos, m_centerPos.x, m_centerPos.y, 0.0);
	m_iScale = glGetUniformLocation(programID, "scale");
		
	GLfloat scaleMatrix[16] = {
		m_Scale.x,	0.0f,		0.0f, 0.0f,
		0.0f,		m_Scale.y,	0.0f, 0.0f,
		0.0f,		0.0f,		1.0f, 0.0f,
		0.0f,		0.0f,		0.0f, 1.0f
	};
	glUniformMatrix4fv(m_iScale, 1, GL_FALSE, scaleMatrix);
		
}

void CRenderComponent::Destroy()
{
}

void CRenderComponent::SetTexture(const string& _strKey, const char* _strFilePath)
{
	m_texture = CResMgr::GetInstance()->Load(_strKey, _strFilePath);
	m_Texid = m_texture->m_texId;
}

void CRenderComponent::LoadPlaneVAO()
{
	float vertices[32] =
	{
		// 위치              // 컬러
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f  // top left 
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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texid);

	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CRenderComponent::SetCenterPos(float x, float y)
{
	m_centerPos.x = x;
	m_centerPos.y = y;
}

void CRenderComponent::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}
