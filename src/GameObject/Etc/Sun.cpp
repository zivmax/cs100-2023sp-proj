#include "Etc.hpp"
#include "utils.hpp"

static const int DISAPPER_TICKS = 300;
static const int POINT_OF_EACH_SUN = 25;
static const int GRAVITY = 1;

Sun::Sun(int x, int y, pGameWorld belonging_world)
    : GameObject(belonging_world, IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM) {}


void Sun::OnClick()
{
    SelfKill();
    int current_sun = m_belonging_world->GetSun();
    m_belonging_world->SetSun(current_sun + POINT_OF_EACH_SUN);
}


FlowerSun::FlowerSun(int x, int y, pGameWorld belonging_world) : Sun(x, y, belonging_world)
{
    m_drop_ticks = 12;
    m_elapsed_ticks = 0;
    m_speed_x = 1;
    m_speed_y = 4;
}


void FlowerSun::Update()
{
    if (m_elapsed_ticks < m_drop_ticks)
    {
        int next_x = GetX() - m_speed_x;
        int next_y = GetY() + m_speed_y;

        // There's gravity.
        m_speed_y -= GRAVITY;

        MoveTo(next_x, next_y);
    }
    else
    {
        if (m_elapsed_ticks - m_drop_ticks == DISAPPER_TICKS)
        {
            // If the sun has been on the ground for 300 ticks, then it will disappear.
            SelfKill();
        }
    }

    m_elapsed_ticks++;
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
    if (m_elapsed_ticks < m_drop_ticks)
    {
        MoveTo(GetX(), GetY() - 1);
    }
    else if (m_elapsed_ticks - m_drop_ticks == DISAPPER_TICKS)
    {
        // If the sun has been on the ground for 300 ticks, then it will disappear.
        SelfKill();
    }

    m_elapsed_ticks++;
}
