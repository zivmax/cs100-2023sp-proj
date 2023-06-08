#include "GameObject.hpp"

class PlantBase : public GameObject
{
    public:
        PlantBase(pGameWorld belonging_world, ImageID imageID, AnimID animID, int HP, int x, int y);

        virtual void OnClick() override;
        virtual void OnCollision(const GameObject &other) override;

    protected:
};


class SunFlower : public PlantBase
{
    public:
        SunFlower(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;


    private:
        int m_production_timer = -1;
        int m_inter_ticks_of_production = -1;
};


class PeaShooter : public PlantBase
{
    public:
        PeaShooter(int x , int y, pGameWorld belonging_world);

        virtual void Update() override;
        void Attack();

    private:
        int m_shoot_cooling_ticks = -1;
        int m_cooling_timer = -1;
};


class WallNut : public PlantBase
{
    public:
        WallNut(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;

    private:
        bool m_is_cracked = false;
};


class CherryBomb : public PlantBase
{
    public:
        CherryBomb(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;

    private:
        int m_explode_timer = -1;
};


class Repeater : public PlantBase
{
    public:
        Repeater(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
        void Attack();

    private:
        int m_cooling_timer = -1;
        int m_first_shoot_cooling_ticks = -1;
        int m_second_shoot_cooling_ticks = -1;
};
