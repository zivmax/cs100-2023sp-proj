#include "Zombies.hpp"

BucketZombie::BucketZombie(int x, int y, pGameWorld belonging_world)
    : ZombieBase(belonging_world, IMGID_BUCKET_HEAD_ZOMBIE, ANIMID_WALK_ANIM, 3, 1300, x, y) {}

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

    UpdateEatingStatus();

    if (!m_is_eating)
    {
        MoveTo(GetX() - 1, GetY());
    }
}