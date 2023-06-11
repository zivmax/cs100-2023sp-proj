#include "GameObject.hpp"
#include <cmath>


GameObject::GameObject(pGameWorld ptr_gameworld, ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : ObjectBase(imageID, x, y, layer, width, height, animID), m_belonging_world(ptr_gameworld)
{
    m_row_on_lawn = (y - FIRST_ROW_CENTER) / LAWN_GRID_HEIGHT + 1;
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


int GameObject::GetLawnRow() const
{
    return m_row_on_lawn;
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
    bool is_collidable = false;

    if (obj1.m_is_dead || obj2.m_is_dead)
    {
        is_collidable = false;
    }
    else if (obj1.m_row_on_lawn == obj2.m_row_on_lawn)
    {
        return false;
    }
    else
    {
        switch (obj1.m_type)
        {
            case ObjectType::ATTACKING_OBJECT:
                if (obj2.m_type == ObjectType::ZOMBIE)
                    is_collidable = true;
                break;

            case ObjectType::PLANT:
                if (obj2.m_type == ObjectType::ZOMBIE)
                    is_collidable = true;
                break;

            case ObjectType::ZOMBIE:
                if (obj2.m_type == ObjectType::ATTACKING_OBJECT || obj2.m_type == ObjectType::PLANT)
                    is_collidable = true;
                break;

            default:
                break;
        }
    }

    return is_collidable;
}


bool GameObject::AreCollidable(const pGameObject &obj1, const pGameObject &obj2)
{
    bool is_collidable = false;

    if (obj1->m_is_dead || obj2->m_is_dead)
    {
        return false;
    }
    else if (obj1->m_row_on_lawn == obj2->m_row_on_lawn)
    {
        return false;
    }
    else
    {
        switch (obj1->m_type)
        {
            case ObjectType::ATTACKING_OBJECT:
                if (obj2->m_type == ObjectType::ZOMBIE)
                    is_collidable = true;
                break;

            case ObjectType::PLANT:
                if (obj2->m_type == ObjectType::ZOMBIE)
                    is_collidable = true;
                break;

            case ObjectType::ZOMBIE:
                if (obj2->m_type == ObjectType::ATTACKING_OBJECT || obj2->m_type == ObjectType::PLANT)
                    is_collidable = true;
                break;

            default:
                break;
        }
    }

    return is_collidable;
}


// Objects on different row will never be considerdd colliding.
bool GameObject::AreColliding(GameObject &obj1, GameObject &obj2)
{
    bool is_colliding = false;

    int diff_x = std::abs(obj1.GetX() - obj2.GetX());
    int boundary_x = obj1.GetWidth() / 2 + obj2.GetWidth() / 2;

    if (diff_x <= boundary_x)
    {
        is_colliding = true;
    }
    else
    {
        is_colliding = false;
    }

    return is_colliding;
}

bool GameObject::AreColliding(pGameObject &obj1, pGameObject &obj2)
{
    bool is_colliding = false;

    int diff_x = std::abs(obj1->GetX() - obj2->GetX());
    int boundary_x = obj1->GetWidth() / 2 + obj2->GetWidth() / 2;

    if (diff_x <= boundary_x)
    {
        is_colliding = true;
    }
    else
    {
        is_colliding = false;
    }

    return is_colliding;
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
