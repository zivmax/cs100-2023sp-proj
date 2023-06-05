#include "Plants.hpp"
#include "Etc.hpp"

static const int FIRST_SHOOT_COOLING_TICKS = 30;
static const int SECOND_SHOOT_COOLING_TICKS = 5;

Repeater::Repeater(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_REPEATER, ANIMID_IDLE_ANIM, 300, x, y)
{
    m_cooling_left_ticks = 0;
    m_first_shoot_cooling_ticks = FIRST_SHOOT_COOLING_TICKS;
    m_second_shoot_cooling_ticks = SECOND_SHOOT_COOLING_TICKS;
}



void Repeater::Update()
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
    else if (m_cooling_left_ticks == 25)
    {

    }

    m_cooling_left_ticks--;
}

void Repeater::Attack()
{
    m_belonging_world->AddObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_belonging_world));
    m_cooling_left_ticks = m_first_shoot_cooling_ticks;
}