#pragma once

class CObject
{
private:
	bool isUndestroyable = false;

public:
	CObject();
	virtual ~CObject();
	virtual void Destroy();

public:
};

