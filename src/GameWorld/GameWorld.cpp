#include "GameWorld.hpp"
#include "Etc.hpp"
#include "GameObject.hpp"
#include "Plants.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}


void GameWorld::Init()
{
    m_objects_ptr.push_back(std::make_shared<BackGround>(shared_from_this()));

    SetWave(0);
    SetSun(0);
}


LevelStatus GameWorld::Update()
{
    for (auto &obj : m_objects_ptr)
    {
        obj->Update();
    }

    for (auto &obj : m_objects_ptr)
    {
        if (obj->IsDead())
        {
            m_objects_ptr.remove(obj);
            break;
        }
    }

    return LevelStatus::ONGOING;
}


pGameObject_weak GameWorld::AddObject(pGameObject new_object_ptr)
{
    pGameObject_weak new_object_weak_ptr = new_object_ptr;
    m_objects_ptr.push_back(std::move(new_object_ptr));

    // Return an weak ptr in case some objects need to watch the object they create
    return new_object_weak_ptr;
}


pGameObject_weak GameWorld::PlantingSeedOnHand(int x, int y)
{
    if (m_object_on_hands == ObjectOnHands::NONE)
    {
        return std::shared_ptr<GameObject>();
    }

    // If the seed is planted succcessfully,
    // the planting spot will get a weak ptr to watch the plant planted on it
    switch (m_object_on_hands)
    {
        case ObjectOnHands::SUN_FLOWER_SEED:
            return AddObject(std::make_shared<SunFlower>(x, y, shared_from_this()));
        default:
            return std::shared_ptr<GameObject>();
    }
}

ObjectOnHands GameWorld::GetObjectOnHands() const
{
    return m_object_on_hands;
}

void GameWorld::CleanUp()
{
    m_objects_ptr.clear();
}
