#include "etc.hpp"

BackGround::BackGround(pGameWorld belonging_world) : GameObject(belonging_world, IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION) {}


void BackGround::Update() {}

void BackGround::OnClick() {}
