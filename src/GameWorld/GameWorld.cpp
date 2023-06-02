#include "GameWorld.hpp"


GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
    m_objects.push_back(std::make_shared<BackGround>());

    SetWave(0);
    SetSun(0);
}

LevelStatus GameWorld::Update()
{
    for (auto &obj : m_objects)
    {
        obj->Update();
    }

    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
}
