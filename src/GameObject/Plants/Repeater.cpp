#include "Etc.hpp"
#include "Plants.hpp"

static const int HP = 300;

static const int FIRST_SHOOT_COOLING_TICKS = 30;
static const int TIMING_OF_SECOND_SHOOT = FIRST_SHOOT_COOLING_TICKS - 5;

Repeater::Repeater(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_REPEATER, ANIMID_IDLE_ANIM, HP, x, y)
{
    m_cooling_timer = 0;
    m_first_shoot_cooling_ticks = FIRST_SHOOT_COOLING_TICKS;
    m_timing_of_second_shoot = TIMING_OF_SECOND_SHOOT;
}


void Repeater::Update()
{
    if (IsDead())
    {
        return;
    }
    else if (m_cooling_timer == 0)
    {
        if (m_belonging_world->AnyZombieOnRow(m_row_on_lawn))
        {
            if (m_belonging_world->AnyZombieRightOf(GetX()))
            {
                Attack();
                
                // The first shoot will reset the cooling timer.
                m_cooling_timer = m_first_shoot_cooling_ticks;  
            }
        }
    }
    else if (m_cooling_timer == m_timing_of_second_shoot)
    {
        // The second shoot will be performed after first shoot 5 ticks,
        // NO MATTER is there zombies.
        Attack();
        m_cooling_timer--;
    }
    else
    {
        m_cooling_timer--;
    }
}


void Repeater::Attack()
{
    m_belonging_world->AddObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, m_belonging_world));
}