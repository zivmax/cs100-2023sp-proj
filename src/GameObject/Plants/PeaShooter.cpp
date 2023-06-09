#include "Etc.hpp"
#include "Plants.hpp"

static const int SHOOT_COOLING_TICKS = 30;

PeaShooter::PeaShooter(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_PEASHOOTER, ANIMID_IDLE_ANIM, 300, x, y)
{
    m_cooling_timer = 0;
    m_shoot_cooling_ticks = SHOOT_COOLING_TICKS;
}


void PeaShooter::Update()
{
    if (IsDead())
    {
        return;
    }
    else if (m_cooling_timer == 0)
    {
        if (m_belonging_world->AnyZombieOnRow(m_row_on_lawn))
        {
            Attack();
        }

        return;
    }
    else
    {
        m_cooling_timer--;
    }
}

void PeaShooter::OnCollision(const GameObject &other)
{
    m_HP -= other.GetAP();
    if (m_HP <= 0)
    {
        SelfKill();
    }
}


void PeaShooter::Attack()
{
    m_belonging_world->AddObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_belonging_world));
    m_cooling_timer = m_shoot_cooling_ticks;
}