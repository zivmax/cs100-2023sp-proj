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

