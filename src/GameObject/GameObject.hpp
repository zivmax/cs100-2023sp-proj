#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include "ObjectBase.hpp"
#include "GameWorld.hpp"
#include <memory>

const double TIME_PER_TICK = (1 / 30);

// Declares the class name GameWorld so that its pointers can be used.
using pGameWorld = std::shared_ptr<GameWorld>;
//using pGameWorld = std::shared_ptr<WorldBase>;


class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
    public:
        using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".
        GameObject() = delete;
        GameObject(const GameObject &other) = delete;
        GameObject(GameObject &&other) = delete;
        GameObject &operator=(const GameObject &other) = delete;
        GameObject &operator=(GameObject &&other) = delete;
        GameObject(pGameWorld ptr_gameworld, ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);
        bool IsDead() const;
        void SelfKill();

    protected:
        std::shared_ptr<GameWorld> m_belonging_world;
        bool m_is_dead = false;
};



#endif // !GAMEOBJECT_HPP__
