#include "GameWorld.hpp"
#include "GameObject.hpp"
#include "Etc.hpp"
#include "Plants.hpp"
#include "Seeds.hpp"


GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}


void GameWorld::Init()
{
    m_objects_ptr.push_back(std::make_shared<BackGround>(shared_from_this()));

    SetWave(0);
    SetSun(50);

    CreatePlantingSpots();
    CreateSeedCards();
    CreateShovel();
}


void GameWorld::CreatePlantingSpots()
{
    // 45 planting spots will be created in total.
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            int x = FIRST_COL_CENTER + i * LAWN_GRID_WIDTH;
            int y = FIRST_ROW_CENTER + j * LAWN_GRID_HEIGHT;
            m_objects_ptr.push_back(std::make_shared<PlantingSpot>(x, y, shared_from_this()));
        }
    }
}

void GameWorld::CreateSeedCards()
{
    int x = 130;
    m_objects_ptr.push_back(std::make_shared<SunFlowerSeed>(x, shared_from_this()));
}

void GameWorld::CreateShovel()
{
    m_objects_ptr.push_back(std::make_shared<Shovel>(shared_from_this()));
}


void GameWorld::HandleCollision()
{
    for (auto &obj1 : m_objects_ptr)
    {
        for (auto &obj2 : m_objects_ptr)
        {
            if (obj1 == obj2)
            {
                continue;
            }
            
            if (GameObject::AreCollidable(*obj1, *obj2))
            {
                if (GameObject::AreColliding(*obj1, *obj2))
                {
                    obj1->OnCollision(*obj2);
                    obj2->OnCollision(*obj1);
                }
            }
        }
    }
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
    pGameObject_weak returned_ptr = pGameObject_weak();

    if (m_object_on_hands == ObjectOnHands::NONE)
    {
        return returned_ptr;
    }


    switch (m_object_on_hands)
    {
        case ObjectOnHands::SUN_FLOWER_SEED:
            returned_ptr = AddObject(std::make_shared<SunFlower>(x, y, shared_from_this()));
            break;
        default:
            break;
    }

    m_object_on_hands = ObjectOnHands::NONE;

    return returned_ptr;
}

ObjectOnHands GameWorld::GetObjectOnHands() const
{
    return m_object_on_hands;
}

void GameWorld::SetObjectOnHands(ObjectOnHands new_object_on_hands)
{
    m_object_on_hands = new_object_on_hands;
}

void GameWorld::CleanUp()
{
    m_objects_ptr.clear();
}
