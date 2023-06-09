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
        virtual void OnCollision(const GameObject &other) override;
        void UpdatePosition();
        void StopEating();



    protected:
        bool m_is_eating = false;
        int m_speed = -1;
};


class RegularZombie : public ZombieBase
{
    public:
        RegularZombie(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
        virtual void OnCollision(const GameObject &other) override;
};


class BucketZombie : public ZombieBase
{
    public:
        BucketZombie(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
        virtual void OnCollision(const GameObject &other) override;

    private:
        bool m_has_bucket = true;
};


class PoleZombie : public ZombieBase
{
    public:
        PoleZombie(int x, int y, pGameWorld belonging_world);

        virtual void Update() override;
        virtual void OnCollision(const GameObject &other) override;
        void ExtendHitBox();
        void StartJump();
        void StopJump();

    private:
        bool m_is_extended = false;
        bool m_is_running = true;
        bool m_is_playing = false;
        int m_jump_anime_frames_left = -1;
        pGameObject_weak m_extended_box = pGameObject_weak();
};
