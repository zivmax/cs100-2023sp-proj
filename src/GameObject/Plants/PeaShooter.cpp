#include "Etc.hpp"
#include "Plants.hpp"

PeaShooter::PeaShooter(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_PEASHOOTER, ANIMID_IDLE_ANIM, 300, x, y)
{
    m_cooling_left_ticks = 0;
    m_shoot_cooling_ticks = 30;
}


void PeaShooter::Update()
{
    if (IsDead())
    {
        return;
    }
    else if (m_cooling_left_ticks == 0)
    {
        if (m_belonging_world->AnyZombieOnRow(m_row_on_lawn))
        {
            Attack();
        }

        return;
    }

    m_cooling_left_ticks--;
}

void PeaShooter::Attack()
{
    m_belonging_world->AddObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_belonging_world));
    m_cooling_left_ticks = m_shoot_cooling_ticks;
}