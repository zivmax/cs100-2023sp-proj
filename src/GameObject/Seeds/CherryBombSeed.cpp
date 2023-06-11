#include "Seeds.hpp"

static const int COST = 150;
static const int COOLING_TICKS = 1200;

CherryBombSeed::CherryBombSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_CHERRY_BOMB, ObjectOnHands::CHERRY_BOMB_SEED, COOLING_TICKS, COST, x) {}

