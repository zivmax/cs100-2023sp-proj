#include "Etc.hpp"

static const int SPEED = 8;

Pea::Pea(int x, int y, pGameWorld belonging_world)
    : AttackingObj(belonging_world, IMGID_PEA, ANIMID_NO_ANIMATION, 20, x, y, 28, 28) {}

void Pea::Update()
{
    if (IsDead())
    {
        return;
    }

    if (GetX() >= WINDOW_WIDTH)
    {
        SelfKill();
        return;
    }

    MoveTo(GetX() + SPEED, GetY());
}


void Pea::OnCollision(const GameObject &other)
{
    if (other.GetAP() != 0)
    {
        SelfKill();
    }
}
