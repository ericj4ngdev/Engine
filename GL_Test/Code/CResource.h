#pragma once


class CResource : public CObject
{
public:
	CResource();
	~CResource() override;
private:
	std::string m_name;
};

 