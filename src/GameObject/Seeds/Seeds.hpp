#include "GameObject.hpp"
#include "ToolKit.hpp"


class SeedBase : public GameObject
{
	public:
        SeedBase(pGameWorld belonging_world, ImageID imageID, ObjectOnHands seed_type, int cooling_ticks, int cost_sun,int x);

		virtual void OnClick() override;
        virtual void Update() override;

	protected:
        int m_cooling_ticks = -1;
        int m_cost_sun = -1;

		ObjectOnHands m_seed_type = ObjectOnHands::UNDEFINED;
};


class SeedCoolDownMask : public GameObject
{
	public:
		SeedCoolDownMask(int x, int y, int last_ticks, pGameWorld belonging_world);

		virtual void OnClick() override;
        virtual void Update() override;

	private:
		int m_remove_timer = -1;
};


class SunFlowerSeed : public SeedBase
{
	public:
        SunFlowerSeed(int x, pGameWorld belonging_world);
        virtual void OnClick() override;
};

class PeaShooterSeed : public SeedBase
{
    public:
        PeaShooterSeed(int x, pGameWorld belonging_world);
        virtual void OnClick() override;
};


class WallNutSeed : public SeedBase
{
    public:
        WallNutSeed(int x, pGameWorld belonging_world);
        virtual void OnClick() override;
};


class CherryBombSeed : public SeedBase
{
    public:
        CherryBombSeed(int x, pGameWorld belonging_world);
        virtual void OnClick() override;
};

class RepeaterSeed : public SeedBase
{
    public:
        RepeaterSeed(int x, pGameWorld belonging_world);
        virtual void OnClick() override;
};
