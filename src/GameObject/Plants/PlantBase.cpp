#include "Plants.hpp"

PlantBase::PlantBase(pGameWorld belonging_world, ImageID imageID, AnimID animID, int HP, int x, int y) : GameObject(belonging_world, imageID, x, y, LAYER_PLANTS, 60, 80, animID)
{
    m_type = ObjectType::PLANT;

    m_HP = HP;

    // The origin of the lawn grid is the most left bottom one.
}

// For all the plants, they should do nothing when being clcked, the PlantingSpot class will take care of the clicks.
void PlantBase::OnClick() 
{
    switch (m_belonging_world->GetObjectOnHands())
    {
        case ObjectOnHands::SHOVEL:
            SelfKill();
            m_belonging_world->SetObjectOnHands(ObjectOnHands::NONE);
            break;
        default:
            break;
    }
}

void PlantBase::OnCollision(const GameObject& other)
{
    m_HP -= 3;
    if (m_HP <= 0)
    {
        SelfKill();
    }
}
