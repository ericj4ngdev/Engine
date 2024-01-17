#pragma once

class CTexture;
class CRenderComponent : public CComponent
{
public:
	void Init() override;
	void Tick() override;
	void Destroy() override;
	void SetTexture();
private:
	CTexture* m_texture = NULL;
	
};

