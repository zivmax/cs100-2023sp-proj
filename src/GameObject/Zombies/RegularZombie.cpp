#include "Zombies.hpp"

static const int HP = 200;
static const int AP = 3;

RegularZombie::RegularZombie(int x, int y, pGameWorld belonging_world)
    : ZombieBase(belonging_world, IMGID_REGULAR_ZOMBIE, ANIMID_WALK_ANIM, AP, HP, x, y)
{
    m_speed = 1;
}


