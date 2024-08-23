#include "include.h"

CStateAttack::CStateAttack(CMegaman* Character) : CStateBase(Character, "Attack")
{
    m_AttackDelay = 0.25f;
    m_AnimationTimer = 0;
}

CStateAttack::~CStateAttack()
{
}

void CStateAttack::Enter()
{
    if (m_Character->m_FSM->GetPreviousState() == m_Character->m_FSM->GetIdleState())
    {
        m_eCurAttackState = ATTACK_STATE::NORMAL_ATTACK;        
    }
    else if (m_Character->m_FSM->GetPreviousState() == m_Character->m_FSM->GetRunState())
    {
        m_eCurAttackState = ATTACK_STATE::RUN_ATTACK;        
    }
    else if (m_Character->m_FSM->GetPreviousState() == m_Character->m_FSM->GetJumpState() || m_Character->m_FSM->GetPreviousState() == m_Character->m_FSM->GetFallState())
    {
        m_eCurAttackState = ATTACK_STATE::JUMP_ATTACK;        
    }
    else
    {
        m_eCurAttackState = ATTACK_STATE::IDLE;
    }
}

void CStateAttack::Update()
{
    if (m_Character->GetbDamaged())
    {
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetHurtState());
    }

    m_AnimationTimer += fDT;    
    // 시간이 끝나면 전환
    if (GetKeyDown(V))
    {
        m_Character->Attack();
        // m_AnimationTimer = 0;
    }
    
    switch (m_eCurAttackState)
    {
    case ATTACK_STATE::IDLE:
        m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetIdleState());
        break;
    case ATTACK_STATE::NORMAL_ATTACK:
    {
        if (m_AnimationTimer < m_AttackDelay)
        {
            if (m_Character->m_iDir == 1)
                m_Character->m_Animator->Play("Attack_Right", true);
            else
                m_Character->m_Animator->Play("Attack_Left", true);
        }
        else
        {
            m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetIdleState());
            m_AnimationTimer = 0;
        }
    }           
        break;
    case ATTACK_STATE::RUN_ATTACK:
    {
        if (m_AnimationTimer < m_AttackDelay)
        {
            if (m_Character->m_iDir == 1)
                m_Character->m_Animator->Play("Run_Attack_Right", true);
            else
                m_Character->m_Animator->Play("Run_Attack_Left", true);
        }
        else
        {
            m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetRunState());
            m_AnimationTimer = 0;
        }
    }            
        break;
    case ATTACK_STATE::JUMP_ATTACK:
    {
        if (m_AnimationTimer < m_AttackDelay)
        {
            if (m_Character->m_iDir == 1)
                m_Character->m_Animator->Play("Jump_Attack_Right", true);
            else
                m_Character->m_Animator->Play("Jump_Attack_Left", true);
        }
        else
        {
            m_Character->m_FSM->TransitionTo(m_Character->m_FSM->GetJumpState());
            m_AnimationTimer = 0;
        }
    }
        break;
    default:
        break;
    }  
}

void CStateAttack::Exit()
{
    m_AnimationTimer = 0;
    m_eCurAttackState = ATTACK_STATE::IDLE;
}
