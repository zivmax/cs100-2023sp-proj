#include "Etc.hpp"
#include "Plants.hpp"

static const int INTER_TICKS_OF_PRODUCTION = 600;

SunFlower::SunFlower(int x, int y, pGameWorld belonging_world) : PlantBase(belonging_world, IMGID_SUNFLOWER, ANIMID_IDLE_ANIM, 300, x, y)
{
    m_production_timer = randInt(30, 600);
    m_inter_ticks_of_production = INTER_TICKS_OF_PRODUCTION;
}


void SunFlower::Update()
{
    if (IsDead()) // If the SunFlower is already dead, finish the func immeadiately.
    {
        return;
    }

    if (m_production_timer == 0) // If the SunFlower has produced enough suns, kill it.
    {
        m_belonging_world->AddObject(std::make_shared<FlowerSun>(GetX(), GetY(), m_belonging_world));
        m_production_timer = m_inter_ticks_of_production;

        return;
    }

    m_production_timer--;
}



void SunFlower::OnCollision(const GameObject &other)
{
    m_HP -= other.GetAP();
    if (m_HP <= 0)
    {
        SelfKill();
    }
}
