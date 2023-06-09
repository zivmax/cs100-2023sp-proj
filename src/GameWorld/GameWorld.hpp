#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "utils.hpp"

class GameObject;
using pGameObject_weak = std::weak_ptr<GameObject>;
using pGameObject = std::shared_ptr<GameObject>;

enum class ZombieType;

enum class ObjectOnHands {
    UNDEFINED,
    NONE,
    SHOVEL,
    SUN_FLOWER_SEED,
    PEA_SHOOTER_SEED,
    WALL_NUT_SEED,
    CHERRY_BOMB_SEED,
    REPEATER_SEED,
};


class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld>
{
    public:
        // Use shared_from_this() instead of "this".
        GameWorld();
        GameWorld(const GameWorld &other) = delete;
        GameWorld(GameWorld &&other) = delete;
        GameWorld &operator=(const GameWorld &other) = delete;
        GameWorld &operator=(GameWorld &&other) = delete;
        virtual ~GameWorld();

        void Init() override;

        LevelStatus Update() override;

        void CleanUp() override;

        pGameObject_weak AddObject(pGameObject new_object);
        pGameObject_weak PlantingSeedOnHand(int x, int y);

        void SetObjectOnHands(ObjectOnHands new_object_on_hands);
        ObjectOnHands GetObjectOnHands() const;

        bool AnyZombieOnRow(int row) const;


    private:
        int m_sun_gen_timer = 0;
        int m_sun_gen_inter_ticks = 0;
        int m_wave_gen_timer = 0;
        int m_wave_gen_inter_ticks = 0;
        std::list<std::shared_ptr<GameObject>> m_objects_ptr;
        ObjectOnHands m_object_on_hands = ObjectOnHands::NONE;

        void CreatePlantingSpots();
        void CreateSeedCards();
        void CreateShovel();

        void HandleCollisions();
        void ExtraEatingUpdateForZombies();


        void UpdateAllObjects();
        void RemoveDeadObject();

        void GenerateSun();
        void GenerateWave();

        template <typename ZombieT>
        void GenerateZombie();

        void GenerateRandomZombies(int total_amount);

        bool IsLost() const;

        int CountZombies() const;
        int CountPlants() const;
        int CountAttackObjs() const;
};


#endif // !GAMEWORLD_HPP__
