#include "Plants.hpp"

static const int HP = 4000;

static const int BROKEN_TIMING = HP / (double) 3;

WallNut::WallNut(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_WALLNUT, ANIMID_IDLE_ANIM, HP, x, y) {}


void WallNut::Update() 
{
    if (IsDead())
    {
        return;
    }
}

void WallNut::OnCollision(const GameObject &other)
{
    m_HP -= other.GetAP();
    if (m_HP <= 0)
    {
        SelfKill();
    }
    else if (m_HP < BROKEN_TIMING && !m_is_cracked)
    {
        m_is_cracked = true;
        ChangeImage(IMGID_WALLNUT_CRACKED);
    }
}