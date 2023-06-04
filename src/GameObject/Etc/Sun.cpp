#include "Etc.hpp"
#include "utils.hpp"


Sun::Sun(int x, int y, pGameWorld belonging_world) : GameObject(belonging_world, IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM) {}


void Sun::OnClick()
{
    SelfKill();
    int current_sun = m_belonging_world->GetSun();
    m_belonging_world->SetSun(current_sun + 25);
}


FlowerSun::FlowerSun(int x, int y, pGameWorld belonging_world) : Sun(x, y, belonging_world)
{
    m_drop_ticks = 12;
    m_elapsed_ticks = 0;
}


void FlowerSun::Update()
{
    if (m_elapsed_ticks <= m_drop_ticks)
    {
        // Increment the elapsed time since the sun started moving.
        m_elapsed_ticks++;

        int t = m_elapsed_ticks; // Calculate the time since the sun started moving.
        int delta_t = 1;

        // Calculate the position of the sun using the parabolic motion formula.
        int next_x = GetX() - 1;                                                           // Calculate horizontal position
        int next_y = GetY() + 4 * delta_t - 0.5 * 1 * delta_t * delta_t - 1 * delta_t * t; // Calculate vertical position

        // Update the position of the sun
        MoveTo(next_x, next_y);
    }
    else
    {
        m_elapsed_ticks++;

        if (m_elapsed_ticks - m_drop_ticks == 300)
        {
            // If the sun has been on the ground for 300 ticks, then it will disappear.
            SelfKill();
        }
    }
}


WorldSun::WorldSun(int x, int y, pGameWorld belonging_world) : Sun(x, y, belonging_world)
{
    // Set the drop time to a random value between 63 and 263, So that
    // the suns will drop on the background.
    m_drop_ticks = randInt(63, 263);
    m_elapsed_ticks = 0;
}


void WorldSun::Update()
{
    if (m_elapsed_ticks != m_drop_ticks)
    {
        MoveTo(GetX(), GetY() - 1);
    }
    else
    {
        m_elapsed_ticks += 1;

        if (m_elapsed_ticks - m_drop_ticks == 300)
        {
            // If the sun has been on the ground for 300 ticks, then it will disappear.
            SelfKill();
        }
    }
}

