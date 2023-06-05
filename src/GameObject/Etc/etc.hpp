#ifndef ETC_HPP__
#define ETC_HPP__


#include "GameObject.hpp"


class EmptyObject : public GameObject
{
    public:
        EmptyObject(pGameWorld belonging_world);

        virtual void Update() override;
        virtual void OnClick() override;
};

class BackGround : public GameObject
{
    public:
        BackGround(pGameWorld belonging_world);

        virtual void Update() override;
        virtual void OnClick() override;
};


class Sun : public GameObject
{
    public:
        Sun(int x, int y, pGameWorld belonging_world);

        virtual void OnClick() override;

    protected:
        int m_drop_ticks = -1;
        int m_elapsed_ticks = -1;
};

class FlowerSun : public Sun
{
    public:
        FlowerSun(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;

    private:
        int m_speed_x = 1;
        int m_speed_y = 4;
};

class WorldSun : public Sun
{
    public:
        WorldSun(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
};


class PlantingSpot : public GameObject
{
    public:
        PlantingSpot(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
        virtual void OnClick() override;
};


class Shovel : public GameObject
{
    public:
        Shovel(pGameWorld belonging_world);

        virtual void Update() override;
        virtual void OnClick() override;
};


class AttackingObj : public GameObject
{
    public:
        AttackingObj(pGameWorld belonging_world, ImageID imageID, AnimID animID, int AP, int x, int y, int width, int height);

        virtual void OnClick() override;
        virtual void OnCollision(const GameObject &other) override;
};


class Pea : public AttackingObj
{
    public:
        Pea(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
};


class Explosion : public AttackingObj
{
    public:
        Explosion(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;

    private:
        int m_last_ticks_left = -1;
};


class ExtendedHitBox : public GameObject
{
    public:
        ExtendedHitBox(int x, int y, int width, int height, pGameWorld belonging_world, pGameObject_weak belonging_obj);

        virtual void Update() override;
        virtual void OnClick() override;
        virtual void OnCollision(const GameObject &other) override;

    private:
        pGameObject_weak m_belonging_obj = pGameObject_weak();
};


#endif // !BACK_GROUND_HPP__