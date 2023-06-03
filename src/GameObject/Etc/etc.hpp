#ifndef ETC_HPP__
#define ETC_HPP__


#include "GameObject.hpp"


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

        void OnClick() override;

    protected:
        int m_drop_ticks = -1;
        int m_elapsed_ticks = -1;
};

class FlowerSun : public Sun
{
    public:
        FlowerSun(int x, int y, pGameWorld belonging_world);

        void Update() override;
};

class WorldSun : public Sun
{
    public:
        WorldSun(int x, int y, pGameWorld belonging_world);

        void Update() override;
};


class PlantingSpot : public GameObject
{
	public:
		PlantingSpot(int x, int y, pGameWorld belonging_world);

        void Update() override;
        void OnClick() override;
};

#endif // !BACK_GROUND_HPP__