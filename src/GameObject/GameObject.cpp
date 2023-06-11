#include "GameObject.hpp"
#include <cmath>


GameObject::GameObject(pGameWorld ptr_gameworld, ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : ObjectBase(imageID, x, y, layer, width, height, animID), m_belonging_world(ptr_gameworld)
{
}

void GameObject::SelfKill()
{
    m_is_dead = true;
}


bool GameObject::IsDead() const
{
    return m_is_dead;
}


bool GameObject::IsColliding() const
{
    return m_is_colliding;
}


int GameObject::GetAP() const
{
    return m_AP;
}


void GameObject::OnCollision(const GameObject &obj) {}


// Funcs bellow are all have two version by func overloading.
bool GameObject::IsPlant(const GameObject &obj)
{
    return obj.m_type == ObjectType::PLANT;
}

bool GameObject::IsPlant(const pGameObject &obj)
{
    return obj->m_type == ObjectType::PLANT;
}


bool GameObject::IsAttackingObject(const GameObject &obj)
{
    return obj.m_type == ObjectType::ATTACKING_OBJECT;
}

bool GameObject::IsAttackingObject(const pGameObject &obj)
{
    return obj->m_type == ObjectType::ATTACKING_OBJECT;
}


bool GameObject::IsZombie(const GameObject &obj)
{
    return obj.m_type == ObjectType::ZOMBIE;
}

bool GameObject::IsZombie(const pGameObject &obj)
{
    return obj->m_type == ObjectType::ZOMBIE;
}


// Every time before check collision of an object, this must be call first.
void GameObject::InitCollisionStatus(GameObject &obj)
{
    obj.m_is_colliding = false;
}

void GameObject::InitCollisionStatus(pGameObject &obj)
{
    obj->m_is_colliding = false;
}


bool GameObject::AreCollidable(const GameObject &obj1, const GameObject &obj2)
{
    bool are_collidable = false;

    if (obj1.m_is_dead || obj2.m_is_dead)
    {
        are_collidable = false;
    }
    else
    {
        switch (obj1.m_type)
        {
            case ObjectType::ATTACKING_OBJECT:
                if (obj2.m_type == ObjectType::ZOMBIE)
                    are_collidable = true;
                break;

            case ObjectType::PLANT:
                if (obj2.m_type == ObjectType::ZOMBIE)
                    are_collidable = true;
                break;

            case ObjectType::ZOMBIE:
                if (obj2.m_type == ObjectType::ATTACKING_OBJECT || obj2.m_type == ObjectType::PLANT)
                    are_collidable = true;
                break;

            default:
                break;
        }
    }

    return are_collidable;
}


bool GameObject::AreCollidable(const pGameObject &obj1, const pGameObject &obj2)
{
    bool are_collidable = false;

    if (obj1->m_is_dead || obj2->m_is_dead)
    {
        return false;
    }
    else
    {
        switch (obj1->m_type)
        {
            case ObjectType::ATTACKING_OBJECT:
                if (obj2->m_type == ObjectType::ZOMBIE)
                    are_collidable = true;
                break;

            case ObjectType::PLANT:
                if (obj2->m_type == ObjectType::ZOMBIE)
                    are_collidable = true;
                break;

            case ObjectType::ZOMBIE:
                if (obj2->m_type == ObjectType::ATTACKING_OBJECT || obj2->m_type == ObjectType::PLANT)
                    are_collidable = true;
                break;

            default:
                break;
        }
    }

    return are_collidable;
}


// Objects on different row will never be considerdd colliding.
bool GameObject::AreColliding(GameObject &obj1, GameObject &obj2)
{
    bool are_colliding = false;

    int diff_x = std::abs(obj1.GetX() - obj2.GetX());
    int diff_y = std::abs(obj1.GetY() - obj2.GetY());

    // The boundary of two objects' collision.
    int boundary_x = obj1.GetWidth() / 2 + obj2.GetWidth() / 2;
    int boundary_y = obj1.GetHeight() / 2 + obj2.GetHeight() / 2;

    if (diff_x <= boundary_x && diff_y <= boundary_y)
    {
        are_colliding = true;
    }
    else
    {
        are_colliding = false;
    }

    return are_colliding;
}

bool GameObject::AreColliding(pGameObject &obj1, pGameObject &obj2)
{
    bool are_colliding = false;

    int diff_x = std::abs(obj1->GetX() - obj2->GetX());
    int diff_y = std::abs(obj1->GetY() - obj2->GetY());

    // The boundary of two objects' collision.
    int boundary_x = obj1->GetWidth() / 2 + obj2->GetWidth() / 2;
    int boundary_y = obj1->GetHeight() / 2 + obj2->GetHeight() / 2;

    if (diff_x <= boundary_x && diff_y <= boundary_y)
    {
        are_colliding = true;
    }
    else
    {
        are_colliding = false;
    }

    return are_colliding;
}


bool GameObject::UpdateCollisionStatus(GameObject &obj1, GameObject &obj2, bool need_call_function)
{
    /*
     * We only check the ollision of two objects.
     * If they are on the same row and their type need to be checked.
     */
    if (GameObject::AreCollidable(obj1, obj2))
    {
        if (GameObject::AreColliding(obj1, obj2))
        {
            obj1.m_is_colliding = true;
            obj2.m_is_colliding = true;

            // Some times we just want to Update the collision status
            if (need_call_function)
            {
                obj1.OnCollision(obj2);
                obj2.OnCollision(obj1);
            }
            return true;
        }
    }

    return false;
}

bool GameObject::UpdateCollisionStatus(pGameObject &obj1, pGameObject &obj2, bool need_call_function)
{
    /*
     * We only check the ollision of two objects.
     * If they are on the same row and their type need to be checked.
     */
    if (GameObject::AreCollidable(obj1, obj2))
    {
        if (GameObject::AreColliding(obj1, obj2))
        {
            obj1->m_is_colliding = true;
            obj2->m_is_colliding = true;

            // Some times we just want to Update the collision status
            if (need_call_function)
            {
                obj1->OnCollision(*obj2);
                obj2->OnCollision(*obj1);
            }
            return true;
        }
    }

    return false;
}
