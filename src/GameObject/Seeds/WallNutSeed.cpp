#include "Seeds.hpp"

WallNutSeed::WallNutSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_WALLNUT, ObjectOnHands::WALL_NUT_SEED, 900, 50, x) {}
