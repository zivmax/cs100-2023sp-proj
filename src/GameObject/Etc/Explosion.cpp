#include "Etc.hpp"

static const int EXPLOSION_DURATION = 3;

class BombShrapnel : public AttackingObj
{
    public:
        BombShrapnel(int x, int y, pGameWorld belonging_world)
            : AttackingObj(belonging_world, IMGID_NONE, ANIMID_NO_ANIMATION, 5000, x, y, LAWN_GRID_WIDTH, LAWN_GRID_HEIGHT)
        {
            m_last_ticks_left = EXPLOSION_DURATION;
        }


        virtual void Update() override
        {
            if (IsDead())
            {
                return;
            }

            if (m_last_ticks_left == 0)
            {
                SelfKill();
            }
            else
            {
                m_last_ticks_left--;
            }
        }

        virtual void OnCollision(const GameObject &other) override {}

    private:
        int m_last_ticks_left = -1;
};


Explosion::Explosion(int x, int y, pGameWorld belonging_world)
    : AttackingObj(belonging_world, IMGID_EXPLOSION, ANIMID_NO_ANIMATION, 0, x, y, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT)
{
    m_last_ticks_left = EXPLOSION_DURATION;

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int new_x = GetX() + i * LAWN_GRID_WIDTH;
            int new_y = GetY() + j * LAWN_GRID_HEIGHT;
            m_belonging_world->AddObject(std::make_shared<BombShrapnel>(new_x, new_y, m_belonging_world));
        }
    }
}

void Explosion::Update()
{
    if (IsDead())
    {
        return;
    }

    if (m_last_ticks_left == 0)
    {
        SelfKill();
    }
    else
    {
        m_last_ticks_left--;
    }
}


void Explosion::OnCollision(const GameObject &other) {}
