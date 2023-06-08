#include "Seeds.hpp"


SeedCoolDownMask::SeedCoolDownMask(int x, int y, int last_ticks, pGameWorld belonging_world)
    : GameObject(belonging_world, IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION)
{
    m_remove_timer = last_ticks;
}


void SeedCoolDownMask::OnClick() {}


void SeedCoolDownMask::Update()
{
    if (m_remove_timer == 0)
    {
        SelfKill();
    }
    else
    {
        m_remove_timer--;
    }
}
