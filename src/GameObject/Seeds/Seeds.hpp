#include "GameObject.hpp"

class SeedBase : public GameObject
{
	public:
        SeedBase(pGameWorld belonging_world, ImageID imageID, ObjectOnHands seed_type, int cooling_ticks, int cost_sun,int x, int y);

		virtual void OnClick() override;
        virtual void Update() override;

	protected:
		int m_cooling_ticks_left = -1;
        int m_cooling_ticks = -1;
        int m_cost_sun = -1;

		ObjectOnHands m_seed_type = ObjectOnHands::NONE;
};


class SeedCoolDownMask : public GameObject
{
	public:
		SeedCoolDownMask(int x, int y, int last_ticks, pGameWorld belonging_world);

		virtual void OnClick() override;
        virtual void Update() override;

	private:
		int m_last_ticks = -1;
};


class SunFlowerSeed : public SeedBase
{
	public:
        SunFlowerSeed(int x, pGameWorld belonging_world);
};