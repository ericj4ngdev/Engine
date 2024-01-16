#ifndef GLMGR_H_
#define GLMGR_H_
class GLMgr
{
	SINGLE(GLMgr);
public :	
	GLuint VAO;
	GLuint VBO;
	GLuint programID;
	static int g_screenWidth;
	static int g_screenHeight;

	float vertices[36] =
	{
		// 위치              // 컬러
		-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.8f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,

		0.8f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f
	};

public:
	void Init();
	void Update();
	void Render();
	void Triangle();
};

#endif