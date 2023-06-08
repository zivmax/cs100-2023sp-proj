#include "Zombies.hpp"

BucketZombie::BucketZombie(int x, int y, pGameWorld belonging_world)
    : ZombieBase(belonging_world, IMGID_BUCKET_HEAD_ZOMBIE, ANIMID_WALK_ANIM, 3, 1300, x, y) 
{
    m_speed = 1;
}

void BucketZombie::Update()
{
    if (IsDead())
    {
        return;
    }

    if (m_HP <= 200 && m_has_bucket)
    {
        ChangeImage(IMGID_REGULAR_ZOMBIE);
        m_has_bucket = false;
    }

    UpdatePosition();

    if (!m_is_colliding && m_is_eating)
    {
        StopEating();
    }
}

void BucketZombie::OnCollision(const GameObject &other)
{
    if (GameObject::IsPlant(other) && !m_is_eating)
    {
        m_is_eating = true;
        PlayAnimation(ANIMID_EAT_ANIM);
    }
    else
    {
        m_HP -= other.GetAP();
        if (m_HP <= 0)
        {
            SelfKill();
        }
    }
}
