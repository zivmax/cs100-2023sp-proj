#include "Seeds.hpp"

CherryBombSeed::CherryBombSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_WALLNUT, ObjectOnHands::CHERRY_BOMB_SEED, 1200, 150, x) {}
