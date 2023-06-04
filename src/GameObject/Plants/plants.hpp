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
        int m_first_production_left_ticks = -1;
        int m_ticks_passed_after_one_generation = -1;
        bool m_first_producted = false;
};
