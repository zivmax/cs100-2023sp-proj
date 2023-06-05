#include "Etc.hpp"

PlantingSpot::PlantingSpot(int x, int y, pGameWorld belonging_world)
    : GameObject(belonging_world, IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION)
{
    m_type = ObjectType::PLANTING_SPOT;
}

void PlantingSpot::Update() {}

void PlantingSpot::OnClick()
{
    switch (m_belonging_world->GetObjectOnHands())
    {
        case ObjectOnHands::NONE:
        case ObjectOnHands::SHOVEL:
            break;
        // All other possibilities are plants' seed.
        default:
            m_belonging_world->PlantingSeedOnHand(GetX(), GetY());
            break;
    }
}
