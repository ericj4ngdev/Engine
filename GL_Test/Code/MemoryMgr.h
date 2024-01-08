#pragma once



class MemoryMgr : public CoreBase
{
public:
	explicit MemoryMgr();
	~MemoryMgr() override;
public:
	void Init() override;

	void ExterminateObjects(bool KillAll = false);

	void ReleaseObject(CObject* object, bool isForce = false);

	// void Update() override;
		
};

