#include "GameWorld.hpp"
#include "Etc.hpp"
#include "GameObject.hpp"
#include "Plants.hpp"
#include "Seeds.hpp"
#include "Zombies.hpp"

// Correct is 50
static const int INIT_SUN = 50;

// Correct is 1200
static const int FIRST_WAVE_TICKS = 1200;
// Correct is 600
static const int FIRST_WAVE_INTER_TICKS = 600;
// Correct is std::max(150, 600 - 20 * GetWave())
#define WAVE_INTER_TICKS std::max(150, 600 - 20 * GetWave())

// Correct is 180
static const int FIRST_WORLD_SUN_GEN_INTER_TICKS = 180;
// Correct is 300
static const int WORLD_SUN_GEN_INTER_TICKS = 300;

// Correct is true
static const bool ENABLE_LOST = true;

GameWorld::GameWorld()
{
    m_sun_gen_inter_ticks = WORLD_SUN_GEN_INTER_TICKS;
    m_wave_gen_inter_ticks = WAVE_INTER_TICKS;
}

GameWorld::~GameWorld() {}


void GameWorld::Init()
{
    m_wave_gen_timer = FIRST_WAVE_TICKS;
    m_sun_gen_timer = FIRST_WORLD_SUN_GEN_INTER_TICKS;

    AddObject(std::make_shared<BackGround>(shared_from_this()));

    SetWave(0);
    SetSun(INIT_SUN);

    CreatePlantingSpots();
    CreateSeedCards();
    CreateShovel();
}


LevelStatus GameWorld::Update()
{

    if (m_sun_gen_timer == 0)
    {
        GenerateSun();
    }

    if (m_wave_gen_timer == 0)
    {
        GenerateWave();
    }

    UpdateAllObjects();
    HandleCollisions();
    RemoveDeadObject();

    if (IsLost())
    {
        return LevelStatus::LOSING;
    }

    ExtraEatingUpdateForZombies();

    m_wave_gen_timer--;
    m_sun_gen_timer--;

    return LevelStatus::ONGOING;
}


void GameWorld::CleanUp()
{
    m_objects_ptr.clear();
    m_object_on_hands = ObjectOnHands::NONE;
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
            AddObject(std::make_shared<PlantingSpot>(x, y, shared_from_this()));
        }
    }
}


void GameWorld::CreateSeedCards()
{
    int x = 130;
    AddObject(std::make_shared<SunFlowerSeed>(x, shared_from_this()));

    x += 60;
    AddObject(std::make_shared<PeaShooterSeed>(x, shared_from_this()));

    x += 60;
    AddObject(std::make_shared<WallNutSeed>(x, shared_from_this()));

    x += 60;
    AddObject(std::make_shared<CherryBombSeed>(x, shared_from_this()));

    x += 60;
    AddObject(std::make_shared<RepeaterSeed>(x, shared_from_this()));
}


void GameWorld::CreateShovel()
{
    AddObject(std::make_shared<Shovel>(shared_from_this()));
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
    for (auto obj_ptr_iter = m_objects_ptr.begin(); obj_ptr_iter != m_objects_ptr.end();)
    {
        if ((*obj_ptr_iter)->IsDead())
        {
            m_objects_ptr.erase(obj_ptr_iter++);
        }
        else
        {
            obj_ptr_iter++;
        }
    }
}


void GameWorld::GenerateSun()
{
    int x = randInt(75, WINDOW_WIDTH - 75);
    int y = WINDOW_HEIGHT - 1;
    AddObject(std::make_shared<WorldSun>(x, y, shared_from_this()));

    m_sun_gen_timer = m_sun_gen_inter_ticks;
}

void GameWorld::GenerateWave()
{
    SetWave(GetWave() + 1);

    int total_amount = (15 + GetWave()) / 10;

    GenerateRandomZombies(total_amount);

    m_wave_gen_inter_ticks = WAVE_INTER_TICKS;
    m_wave_gen_timer = m_wave_gen_inter_ticks;
}


void GameWorld::GenerateRandomZombies(int total_amount)
{
    int p1 = 20;
    int p2 = 2 * std::max(GetWave() - 8, 0);
    int p3 = 3 * std::max(GetWave() - 15, 0);

    for (int i = 0; i < total_amount; i++)
    {
        int random_num = randInt(1, p1 + p2 + p3);
        if (random_num <= p1)
        {
            // RegularZombie
            GenerateZombie<RegularZombie>();
        }
        else if (random_num <= p1 + p2)
        {
            // PoleZombie
            GenerateZombie<PoleZombie>();
        }
        else
        {
            // BucketZombie
            GenerateZombie<BucketZombie>();
        }
    }
}

template <typename ZombieT>
void GameWorld::GenerateZombie()
{
    int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
    int y = FIRST_ROW_CENTER + randInt(0, GAME_ROWS - 1) * LAWN_GRID_HEIGHT;
    AddObject(std::make_shared<ZombieT>(x, y, shared_from_this()));
}


bool GameWorld::IsLost() const
{
    for (auto &obj_ptr : m_objects_ptr)
    {
        if (GameObject::IsZombie(obj_ptr) && obj_ptr->GetX() < 0)
        {
            if (ENABLE_LOST)
            {
                return true;
            }
            else
            {
                obj_ptr->SelfKill();
            }
        }
    }

    return false;
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

        case ObjectOnHands::PEA_SHOOTER_SEED:
            returned_ptr = AddObject(std::make_shared<PeaShooter>(x, y, shared_from_this()));
            break;

        case ObjectOnHands::WALL_NUT_SEED:
            returned_ptr = AddObject(std::make_shared<WallNut>(x, y, shared_from_this()));
            break;

        case ObjectOnHands::CHERRY_BOMB_SEED:
            returned_ptr = AddObject(std::make_shared<CherryBomb>(x, y, shared_from_this()));
            break;

        case ObjectOnHands::REPEATER_SEED:
            returned_ptr = AddObject(std::make_shared<Repeater>(x, y, shared_from_this()));
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


bool GameWorld::AnyZombieOnRow(int request_row) const
{
    for (auto &obj_ptr : m_objects_ptr)
    {
        if (GameObject::IsZombie(obj_ptr) && obj_ptr->GetLawnRow() == request_row)
        {
            return true;
        }
    }

    return false;
}

void GameWorld::ExtraEatingUpdateForZombies()
{
    for (auto &obj_ptr1 : m_objects_ptr)
    {
        if (GameObject::IsZombie(obj_ptr1) && obj_ptr1->IsColliding())
        {
            GameObject::InitCollisionStatus(obj_ptr1);

            for (auto &obj_ptr2 : m_objects_ptr)
            {
                if (GameObject::IsPlant(obj_ptr2))
                {
                    // the `false` param means no func call in `UpdateCollisionStatus`
                    GameObject::UpdateCollisionStatus(obj_ptr1, obj_ptr2, false);
                }
            }
            /*
             * This Update Will Only make the not colliding but
             * eating Zomibie Stop Eating.
             */
            if (obj_ptr1->IsColliding() == false)
            {
                obj_ptr1->Update();
            }
        }
    }
}
