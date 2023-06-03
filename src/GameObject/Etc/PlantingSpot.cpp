#include "etc.hpp"

PlantingSpot::PlantingSpot(int x, int y, pGameWorld belonging_world) : GameObject(belonging_world, IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION) {}

void PlantingSpot::Update() {}

void PlantingSpot::OnClick()
{
}
