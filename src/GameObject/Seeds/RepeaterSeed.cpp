#include "Seeds.hpp"

RepeaterSeed::RepeaterSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_REPEATER, ObjectOnHands::REPEATER_SEED, 240, 200, x) {}


void RepeaterSeed::OnClick()
{
    int current_sun = m_belonging_world->GetSun();
    switch (m_belonging_world->GetObjectOnHands())
    {
        case ObjectOnHands::NONE:
            if (current_sun >= m_cost_sun)
            {
                m_belonging_world->SetObjectOnHands(m_seed_type);
                m_belonging_world->SetSun(current_sun - m_cost_sun);
                m_belonging_world->AddObject(std::make_shared<SeedCoolDownMask>(GetX(), GetY(), m_cooling_ticks, m_belonging_world));
            }
            break;

        default:
            break;
    }
}
