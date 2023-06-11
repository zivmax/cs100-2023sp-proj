#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include "GameWorld.hpp"
#include "ObjectBase.hpp"
#include <memory>
 


// Declares the class name GameWorld so that its pointers can be used.
using pGameWorld = std::shared_ptr<GameWorld>;

enum class ObjectType {
    UNDEFINED,
    ATTACKING_OBJECT,
    PLANTING_SPOT,
    HANDIBLE,
    PLANT,
    ZOMBIE,
};


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

        void SelfKill();
        bool IsDead() const;
        bool IsColliding() const;
        virtual void OnCollision(const GameObject &other);

        int GetAP() const;
        int GetLawnRow() const;

        static bool IsPlant(const GameObject &obj);
        static bool IsPlant(const pGameObject &obj);

        static bool IsAttackingObject(const GameObject &obj);
        static bool IsAttackingObject(const pGameObject &obj);

        static bool IsZombie(const GameObject &obj);
        static bool IsZombie(const pGameObject &obj);

        static void InitCollisionStatus(GameObject &obj);
        static void InitCollisionStatus(pGameObject &obj);

        static bool AreCollidable(const GameObject &obj1, const GameObject &obj2);
        static bool AreCollidable(const pGameObject &obj1, const pGameObject &obj2);

        static bool AreColliding(GameObject &obj1, GameObject &obj2);
        static bool AreColliding(pGameObject &obj1, pGameObject &obj2);

        static bool UpdateCollisionStatus(GameObject &obj1, GameObject &obj2, bool need_call_function = true);
        static bool UpdateCollisionStatus(pGameObject &obj1, pGameObject &obj2, bool need_call_function = true);


    protected:
        int m_AP = 0;
        int m_HP = 1;
        int m_row_on_lawn = -1;
        bool m_is_dead = false;
        bool m_is_colliding = false;
        ObjectType m_type = ObjectType::UNDEFINED;
        pGameWorld m_belonging_world;
};




#endif // !GAMEOBJECT_HPP__
