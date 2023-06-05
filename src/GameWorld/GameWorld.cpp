#include "GameWorld.hpp"
#include "Etc.hpp"
#include "GameObject.hpp"
#include "Plants.hpp"
#include "Seeds.hpp"
#include "Zombies.hpp"


GameWorld::GameWorld()
{
    m_sun_gen_left_ticks = 180;
    m_wave_gen_left_ticks = 10;
    m_sun_gen_inter_ticks = 300;
    m_wave_gen_inter_ticks = std::max(150, 600 - 20 * GetWave());
}

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
    // 45 (9 * 5) planting spots will be created in total.
    for (size_t i = 0; i < GAME_COLS; i++)
    {
        for (size_t j = 0; j < GAME_ROWS; j++)
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


void GameWorld::HandleCollisions()
{
    for (auto &obj_ptr : m_objects_ptr)
    {
        GameObject::InitCollisionStatus(obj_ptr);
    }


    for (auto iter1 = m_objects_ptr.begin(); iter1 != m_objects_ptr.end(); ++iter1)
    {
        for (auto iter2 = iter1; iter2 != m_objects_ptr.end(); ++iter2)
        {
            if (*iter1 == *iter2)
            {
                continue;
            }

            GameObject::UpdateCollisionStatus(*iter1, *iter2);
        }
    }
}


void GameWorld::UpdateAllObjects()
{
    for (auto &obj_ptr : m_objects_ptr)
    {
        obj_ptr->Update();
    }
}


// This func remove all the dead object's shared ptr from the m_objects_ptr list.
void GameWorld::RemoveDeadObject()
{
    for (auto &obj_ptr : m_objects_ptr)
    {
        if (obj_ptr->IsDead())
        {
            m_objects_ptr.remove(obj_ptr);
            break;
        }
    }
}


void GameWorld::GenerateSun()
{
    int x = randInt(75, WINDOW_WIDTH - 75);
    int y = WINDOW_HEIGHT - 1;
    m_objects_ptr.push_back(std::make_shared<WorldSun>(x, y, shared_from_this()));
}

void GameWorld::GenerateWave()
{
    double p1 = 20;
    double p2 = 2 * std::max(GetWave() - 8, 0);
    double p3 = 3 * std::max(GetWave() - 15, 0);

    double P_regular_zombie = p1 / (p1 + p2 + p3);
    double P_bucket_zombie = p2 / (p1 + p2 + p3);
    double P_pole_zombie = p3 / (p1 + p2 + p3);

    int total_amount = (15 + GetWave()) / 10;

    int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
    int y = FIRST_ROW_CENTER + randInt(0, GAME_ROWS - 1) * LAWN_GRID_HEIGHT;

    m_objects_ptr.push_back(std::make_shared<RegularZombie>(x, y, shared_from_this()));

    SetWave(GetWave() + 1);
    m_wave_gen_inter_ticks = std::max(150, 600 - 20 * GetWave());
}

LevelStatus GameWorld::Update()
{
    if (m_sun_gen_left_ticks == 0)
    {
        GenerateSun();
        m_sun_gen_left_ticks = m_sun_gen_inter_ticks;
    }
    else
    {
        m_sun_gen_left_ticks--;
    }

    if (m_wave_gen_left_ticks == 0)
    {
        GenerateWave();
        m_wave_gen_left_ticks = m_wave_gen_inter_ticks;
    }
    else
    {
        m_wave_gen_left_ticks--;
    }

    UpdateAllObjects();

    HandleCollisions();

    RemoveDeadObject();

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
