#pragma once

class CScene;

class CSceneMgr
{
public:
	SINGLE(CSceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];
	CScene*		m_pCurScene;
public:
	void Init();
	void Update();
	void Render();
};

