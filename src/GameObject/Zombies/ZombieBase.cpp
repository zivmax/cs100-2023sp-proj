#include "Zombies.hpp"

ZombieBase::ZombieBase(pGameWorld belonging_world, ImageID imageID, AnimID animID, int AP, int HP, int x, int y) : GameObject(belonging_world, imageID, x, y, LAYER_ZOMBIES, 20, 80, animID)
{
    m_type = ObjectType::ZOMBIE;

    m_HP = HP;
    m_AP = AP;
}


void ZombieBase::OnClick() {}


void ZombieBase::OnCollision(const GameObject &other)
{
    if (GameObject::IsPlant(other) && !m_is_eating)
    {
        m_is_eating = true;
        PlayAnimation(ANIMID_EAT_ANIM);
    }
    else
    {
        m_HP -= other.GetAP();
        if (m_HP <= 0)
        {
            SelfKill();
        }
    }
}
