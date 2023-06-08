#include "Plants.hpp"

WallNut::WallNut(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_WALLNUT, ANIMID_IDLE_ANIM, 4000, x, y) {}


void WallNut::Update() 
{
    if (IsDead())
    {
        return;
    }

    if (m_HP < 4000 / (double) 3 && !m_is_cracked)
    {
        STOP();
        m_is_cracked = true;
        ChangeImage(IMGID_WALLNUT_CRACKED);
    }
}

void WallNut::OnCollision(const GameObject &other)
{
    m_HP -= other.GetAP();
    if (m_HP <= 0)
    {
        SelfKill();
    }
}