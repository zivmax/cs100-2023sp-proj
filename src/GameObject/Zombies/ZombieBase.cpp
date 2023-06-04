#include "Zombies.hpp"

ZombieBase::ZombieBase(pGameWorld belonging_world, ImageID imageID, AnimID animID, int AP, int HP, int x, int y) : GameObject(belonging_world, imageID, x, y, LAYER_ZOMBIES, 20, 80, animID)
{
    m_HP = HP;
    m_AP = AP;
}


void ZombieBase::OnClick() {}


void ZombieBase::OnCollision(const GameObject &other)
{
    if (GameObject::IsPlant(other))
    {
        m_is_eating = true;
    }
    else
    {
        m_HP -= 20;
        if (m_HP <= 0)
        {
            SelfKill();
        }
    }
}
