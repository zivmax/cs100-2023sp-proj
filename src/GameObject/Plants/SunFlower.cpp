#include "Etc.hpp"
#include "Plants.hpp"

SunFlower::SunFlower(int x, int y, pGameWorld belonging_world) : PlantBase(belonging_world, IMGID_SUNFLOWER, ANIMID_IDLE_ANIM, 300, x, y)
{
    m_first_production_left_ticks = randInt(30, 600);
    m_ticks_passed_after_one_generation = 0;
}


void SunFlower::Update()
{
    if (IsDead())
    {
        return;
    }
    else
    {
        // m_first_producted repersent if the sunflower has produced the first sun.
        if (!m_first_producted)
        {
            if (m_first_production_left_ticks == 0)
            {
                m_first_production_left_ticks = -1;
                m_belonging_world->AddObject(std::make_shared<FlowerSun>(GetX(), GetY(), m_belonging_world));
                m_ticks_passed_after_one_generation = 0;
            }
            else
            {
                m_first_production_left_ticks += 1;
            }
        }
        else
        {
            if (m_ticks_passed_after_one_generation == 600)
            {
				m_ticks_passed_after_one_generation = 0;
				m_belonging_world->AddObject(std::make_shared<FlowerSun>(GetX(), GetY(), m_belonging_world));
			}
            else
            {
				m_ticks_passed_after_one_generation += 1;
			}
		}
    }
}
