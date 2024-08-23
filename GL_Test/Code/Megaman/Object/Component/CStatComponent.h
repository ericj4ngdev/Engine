#pragma once

class CStatComponent : public CComponent
{
public:
    COMPONENT_DEFINE_CONSTRUCTOR(CStatComponent)
    void Init() override;
    void Update() override;
    void FinalUpdate() override;
    void Render() override;
    void Destroy() override;
    virtual ~CStatComponent();

    void TakeDamage(float damage, int dir);
    bool DecreaseHP(float damage);

    float GetHP() { return m_CurrentHP; }
    void SetHP(float hp) { m_CurrentHP = hp; }
    void SetFullHP() { m_CurrentHP = m_MaxHP; }

private:
    float m_CurrentHP;
    float m_MaxHP;
    int m_Life;
    bool m_bInvincible;
    float m_bInvincibleTimer;
};

