#include "Etc.hpp"

static const int AP = 5000;

static const int EXPLOSION_DURATION = 3;

Explosion::Explosion(int x, int y, pGameWorld belonging_world)
    : AttackingObj(belonging_world, IMGID_EXPLOSION, ANIMID_NO_ANIMATION, 5000, x, y, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT)
{
    m_last_ticks_left = EXPLOSION_DURATION;
}


void Explosion::Update()
{
    if (IsDead())
    {
        return;
    }

    if (m_last_ticks_left == 0)
    {
        SelfKill();
    }
    else
    {
        m_last_ticks_left--;
    }
}


void Explosion::OnCollision(const GameObject &other) {}
