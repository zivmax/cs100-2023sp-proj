#include "GameObject.hpp"

class ZombieBase : public GameObject
{
    public:
        ZombieBase(pGameWorld belonging_world, ImageID imageID, AnimID animID, int AP, int HP, int x, int y);

        virtual void OnClick() override;
        void OnCollision(const GameObject &other) override;


    protected:
    	int m_HP = -1;
        bool m_is_eating = false;
};