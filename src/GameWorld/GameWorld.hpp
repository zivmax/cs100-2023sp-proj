#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "utils.hpp"

class GameObject;
using pGameObject_weak = std::weak_ptr<GameObject>;
using pGameObject = std::shared_ptr<GameObject>;

enum class ObjectOnHands {
    NONE,
    SHOVEL,
    SUN_FLOWER_SEED,
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

        void CreatePlantingSpots();
        void CreateSeedCards();
        void CreateShovel();

        LevelStatus Update() override;

        pGameObject_weak AddObject(pGameObject new_object);

        pGameObject_weak PlantingSeedOnHand(int x, int y);

        void SetObjectOnHands(ObjectOnHands new_object_on_hands);
        ObjectOnHands GetObjectOnHands() const;

        void CleanUp() override;

    private:
        std::list<std::shared_ptr<GameObject>> m_objects_ptr;
        ObjectOnHands m_object_on_hands = ObjectOnHands::NONE;
};




#endif // !GAMEWORLD_HPP__
