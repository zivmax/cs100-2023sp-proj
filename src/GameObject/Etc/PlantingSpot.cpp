#include "Etc.hpp"

PlantingSpot::PlantingSpot(int x, int y, pGameWorld belonging_world) : GameObject(belonging_world, IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION) 
{
    planted_object = std::weak_ptr<GameObject>();
}

void PlantingSpot::Update() {}

void PlantingSpot::OnClick()
{
    switch (m_belonging_world->GetObjectOnHands())
    {
        case ObjectOnHands::NONE:
            break;
        case ObjectOnHands::SHOVEL:
            if (!planted_object.expired())
            {
                planted_object.lock()->SelfKill();
                planted_object = std::weak_ptr<GameObject>();
            }
            break;
        default:
            planted_object = m_belonging_world->PlantingSeedOnHand(GetX(), GetY());
            break;
    }
}
