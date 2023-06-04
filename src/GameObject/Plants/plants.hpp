#include "GameObject.hpp"

class PlantBase : public GameObject
{
    public:
        PlantBase(pGameWorld belonging_world, ImageID imageID, AnimID animID, int HP, int x, int y);

        virtual void OnClick() override;

    protected:
        int m_HP = -1;
        int m_col_on_lawn = -1;
        int m_row_on_lawn = -1;
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
