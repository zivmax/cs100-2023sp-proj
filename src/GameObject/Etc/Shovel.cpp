#include "Etc.hpp"

Shovel::Shovel(pGameWorld belonging_world) 
    : GameObject(belonging_world, IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, LAYER_UI, 50, 50, ANIMID_NO_ANIMATION) 
{
    m_type = ObjectType::HANDIBLE;
}

void Shovel::Update() {}

void Shovel::OnClick()
{
    switch (m_belonging_world->GetObjectOnHands())
    {
        case ObjectOnHands::NONE:
            m_belonging_world->SetObjectOnHands(ObjectOnHands::SHOVEL);
            break;
        case ObjectOnHands::SHOVEL:
            m_belonging_world->SetObjectOnHands(ObjectOnHands::NONE);
            break;

        // When gamer is holding a seed, he can't use shovel.
        default:
            break;
    }
}
