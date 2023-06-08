#include "Etc.hpp"
#include "Zombies.hpp"


static const int POLE_ZOMBIE_JUMP_ANIME_FRAMES = 42;

PoleZombie::PoleZombie(int x, int y, pGameWorld belonging_world)
    : ZombieBase(belonging_world, IMGID_POLE_VAULTING_ZOMBIE, ANIMID_RUN_ANIM, 3, 340, x, y)
{
    m_speed = 2;
    m_jump_anime_frames_left = POLE_ZOMBIE_JUMP_ANIME_FRAMES;

    // This will Extend a new hitbox for pole zombie
    ExtendHitBox();
}


void PoleZombie::ExtendHitBox()
{
    // The Extended Box will be 40 pixels to the left of the original box
    pGameObject ExtendedBox = std::make_shared<ExtendedHitBox>(
        GetX() - 40, GetY(), GetWidth(), GetHeight(), m_belonging_world, shared_from_this());

    m_extended_box = m_belonging_world->AddObject(ExtendedBox);
}


void PoleZombie::StartJump()
{
    PlayAnimation(ANIMID_JUMP_ANIM);
    m_is_running = false;
    m_is_playing = true;
    m_speed = 1;

    // After jumped, the pole zombie won't need the extended box anymore
    m_extended_box.lock()->SelfKill();
    m_extended_box = pGameObject_weak();
}


void PoleZombie::Update()
{
    if (IsDead())
    {
        return;
    }

    if (m_is_running && m_extended_box.lock()->IsColliding())
    {
        StartJump();
    }
    else if (m_is_playing)
    {
        m_jump_anime_frames_left--;

        if (m_jump_anime_frames_left == 0)
        {
            m_is_playing = false;
            MoveTo(GetX() - 150, GetY());
            PlayAnimation(ANIMID_WALK_ANIM);
        }
    }

    if (!m_is_playing)
    {
        UpdatePosition();
    }

    if (!m_is_running && !m_is_playing && !m_is_colliding && m_is_eating)
    {
        StopEating();
    }
}
