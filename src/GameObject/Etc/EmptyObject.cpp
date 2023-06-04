#include "Etc.hpp"

EmptyObject::EmptyObject(pGameWorld belonging_world) : GameObject(belonging_world, IMGID_NONE, -100, -100, MAX_LAYERS, 0, 0, ANIMID_NO_ANIMATION) {}

void EmptyObject::Update() {}
void EmptyObject::OnClick() {}

