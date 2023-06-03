#include "GameWorld.hpp"
#include "plants.hpp"
#include "zombies.hpp"
#include "etc.hpp"


GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
    m_objects.push_back(std::make_shared<BackGround>(shared_from_this()));

    SetWave(0);
    SetSun(0);
}

LevelStatus GameWorld::Update()
{
    for (auto &obj : m_objects)
    {
        obj->Update();
    }

    for (auto &obj : m_objects)
    {
        if (obj->IsDead())
		{
			m_objects.remove(obj);
			break;
		}
    }

    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
}
