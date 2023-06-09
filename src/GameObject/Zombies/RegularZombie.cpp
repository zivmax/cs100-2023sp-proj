#include "Zombies.hpp"

RegularZombie::RegularZombie(int x, int y, pGameWorld belonging_world)
    : ZombieBase(belonging_world, IMGID_REGULAR_ZOMBIE, ANIMID_WALK_ANIM, 3, 200, x, y)
{
    m_speed = 1;
}

void RegularZombie::Update()
{
    if (IsDead())
    {
        return;
    }

    if (!m_is_colliding)
    {
        if (m_is_eating)
        {
            StopEating();
        }
        else
        {
            // Only when Zombie is both eating and colliding, it won't move
            UpdatePosition();
        }
    }
}

void RegularZombie::OnCollision(const GameObject &other)
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
