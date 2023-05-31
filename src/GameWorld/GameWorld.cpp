#include "GameWorld.hpp"


GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
    SetWave(0);
    SetSun(0);
}

LevelStatus GameWorld::Update()
{
    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
}
