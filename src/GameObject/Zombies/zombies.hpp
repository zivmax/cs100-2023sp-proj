#include "GameObject.hpp"

enum class ZombieType {
    REGULAR,
    BUCKET,
    POLE,
};

class ZombieBase : public GameObject
{
    public:
        ZombieBase(pGameWorld belonging_world, ImageID imageID, AnimID animID, int AP, int HP, int x, int y);

        virtual void OnClick() override;
        void OnCollision(const GameObject &other) override;
        void UpdateEatingStatus();


    protected:
        bool m_is_eating = false;
};

class RegularZombie : public ZombieBase
{
    public:
        RegularZombie(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
};


class BucketZombie : public ZombieBase
{
    public:
        BucketZombie(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;

    private:
        bool m_has_bucket = true;
};

class PoleZombie : public ZombieBase
{
    public:
        PoleZombie(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
};
