#include "Etc.hpp"
#include "Plants.hpp"

static const int BURNING_TIME = 15;

CherryBomb::CherryBomb(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_CHERRY_BOMB, ANIMID_IDLE_ANIM, 4000, x, y)
{
    m_explode_timer = BURNING_TIME;
}


void CherryBomb::Update()
{
    if (IsDead())
    {
        return;
    }

    if (m_explode_timer == 0)
    {
        m_belonging_world->AddObject(std::make_shared<Explosion>(GetX(), GetY(), m_belonging_world));
        SelfKill();
        return;
    }

    m_explode_timer--;
}
