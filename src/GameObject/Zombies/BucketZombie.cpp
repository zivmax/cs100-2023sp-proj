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

    if (!(m_is_eating && m_is_colliding))
    {
        MoveTo(GetX() - 1, GetY());
    }

    UpdateStopEating();
}