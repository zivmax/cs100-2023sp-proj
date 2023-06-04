#include "Seeds.hpp"


SeedBase::SeedBase(pGameWorld belonging_world, ImageID imageID, ObjectOnHands seed_type, int cooling_ticks, int cost_sun, int x, int y) : GameObject(belonging_world, imageID, x, y, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION)
{
    m_cooling_ticks = cooling_ticks;
    m_seed_type = seed_type;
    m_cost_sun = cost_sun;
    m_cooling_ticks_left = 0;
}


void SeedBase::OnClick()
{
    if (m_cooling_ticks_left == 0)
    {
        int current_sun = m_belonging_world->GetSun();
        switch (m_belonging_world->GetObjectOnHands())
        {
            case ObjectOnHands::NONE:

                if (current_sun >= m_cost_sun)
                {
                    m_belonging_world->SetObjectOnHands(m_seed_type);
                    m_belonging_world->SetSun(current_sun - m_cost_sun);
                    m_cooling_ticks_left = m_cooling_ticks;
                    m_belonging_world->AddObject(std::make_shared<SeedCoolDownMask>(GetX(), GetY(), m_cooling_ticks, m_belonging_world));
                }
                break;

            default:
                break;
        }
    }
}


void SeedBase::Update()
{
    if (m_cooling_ticks_left > 0)
    {
        m_cooling_ticks_left--;
    }
}
