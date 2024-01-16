#pragma once

class CTexture;
class CRenderComponent : public CComponent
{
public:
	void Init() override;
	void Start() override;
	void Tick(float elapsedTime) override;
	void Destroy() override;
	void SetTexture();
private:
	CTexture* m_texture = NULL;
	
};

