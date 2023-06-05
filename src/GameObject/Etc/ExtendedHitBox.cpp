#include "Etc.hpp"


ExtendedHitBox::ExtendedHitBox(int x, int y, int width, int height, pGameWorld belonging_world, pGameObject_weak belonging_obj)
    : GameObject(belonging_world, IMGID_NONE, x, y, LAYER_ZOMBIES, width, height, ANIMID_NO_ANIMATION)
{
    m_type = ObjectType::ZOMBIE;
    m_AP = 0;
    m_belonging_obj = belonging_obj;
}

void ExtendedHitBox::Update()
{
    if (IsDead())
    {
        return;
    }
    
    if (m_belonging_obj.expired())
    {
        SelfKill();
    }

    if (GetX() > 1)
    {
        MoveTo(m_belonging_obj.lock()->GetX() - 40, m_belonging_obj.lock()->GetY());
    }

}

void ExtendedHitBox::OnCollision(const GameObject &other)
{
    if (!GameObject::IsPlant(other))
    {
        m_is_colliding = false;
    }
}

void ExtendedHitBox::OnClick() {}
