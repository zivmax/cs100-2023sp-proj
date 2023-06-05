#include <memory>

#include "GameManager.hpp"
#include "GameWorld.hpp"

long long g_ticks = 0;

int main(int argc, char **argv)
{
    std::shared_ptr<WorldBase> world = std::make_shared<GameWorld>();

    GameManager::Instance().Play(argc, argv, world);
}