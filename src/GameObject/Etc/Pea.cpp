#include "Etc.hpp"

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

    MoveTo(GetX() + 8, GetY());
}
