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

template<typename T1, typename T2>
void SafeDeleteMap(map<T1, T2>& m)
{
	typename map<T1, T2>::iterator iter = m.begin();

	for (; iter != m.end(); ++iter)
	{
		if (nullptr != iter->second) {
			delete iter->second;
		}
	}
	m.clear();
}
