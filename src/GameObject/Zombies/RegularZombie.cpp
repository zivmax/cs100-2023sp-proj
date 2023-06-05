#include "Zombies.hpp"

RegularZombie::RegularZombie(int x, int y, pGameWorld belonging_world)
    : ZombieBase(belonging_world, IMGID_REGULAR_ZOMBIE, ANIMID_WALK_ANIM, 3, 200, x, y) {}

void RegularZombie::Update()
{
    if (IsDead())
    {
        return;
    }

    UpdateEatingStatus();

    if (!m_is_eating)
    {
        MoveTo(GetX() - 1, GetY());
    }
}