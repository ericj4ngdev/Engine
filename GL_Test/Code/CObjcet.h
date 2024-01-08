#pragma once
class CObject
{
private:
	bool isUndestroyable = false;

protected:
	std::string m_hash;

public:
	CObject();

	virtual ~CObject();
	virtual void Exterminate() = 0;
	virtual void Destroy();

public:
	friend class MemoryMgr;

};

