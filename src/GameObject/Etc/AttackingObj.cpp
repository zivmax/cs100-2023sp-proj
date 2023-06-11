#include "Etc.hpp"


AttackingObj::AttackingObj(pGameWorld belonging_world, ImageID imageID, AnimID animID, int AP, int x, int y, int width, int height)
    : GameObject(belonging_world, imageID, x, y, LAYER_PROJECTILES, width, height, animID)
{
    m_type = ObjectType::ATTACKING_OBJECT;
    m_AP = AP;
}


void AttackingObj::OnClick() {}

