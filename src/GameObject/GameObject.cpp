#include "GameObject.hpp"


GameObject::GameObject(pGameWorld ptr_gameworld, ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID) : ObjectBase(imageID, x, y, layer, width, height, animID), m_belonging_world(ptr_gameworld) {}


bool GameObject::IsDead() const
{
    return m_is_dead;
}