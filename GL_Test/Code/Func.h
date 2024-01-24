#pragma once

class CGameObject;

void CreateObject(CGameObject* pObj, GROUP_TYPE eGroup);
void DeleteObject(CGameObject* pObj);
void ChangeScene(SCENE_TYPE eNext);

template<typename T>
void SafeDeleteVec(vector<T>& vec) 
{
	for (int i = 0; i < vec.size(); i++) 
	{
		if (nullptr != vec[i]) 
		{
			delete vec[i];
		}
	}
	vec.clear();
}
