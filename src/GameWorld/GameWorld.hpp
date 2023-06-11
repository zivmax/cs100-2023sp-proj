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

        void SetObjectOnHands(ObjectOnHands new_object_on_hands);
        ObjectOnHands GetObjectOnHands() const;
        pGameObject_weak PlantingSeedOnHand(int x, int y);

        bool AnyZombieOnRow(int request_row) const;
        bool AnyZombieRightOf(int request_x) const;

        pGameObject_weak AddObject(pGameObject new_object);

    private:
        int m_sun_gen_timer = 0;
        int m_wave_gen_timer = 0;
        std::list<std::shared_ptr<GameObject>> m_objects_ptr;
        ObjectOnHands m_object_on_hands = ObjectOnHands::NONE;

        void CreatePlantingSpots();
        void CreateSeedCards();
        void CreateShovel();


        void GenerateSun();
        void GenerateWave();
        void GenerateRandomZombies(int total_amount);
        template <typename ZombieT>
        void GenerateZombie();


        void UpdateAllObjects();
        void HandleCollisions();
        void RemoveDeadObjects();


        bool IsLost() const;
};


#endif // !GAMEWORLD_HPP__
