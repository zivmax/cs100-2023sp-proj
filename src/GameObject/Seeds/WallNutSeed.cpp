#include "Seeds.hpp"

static const int COST = 50;
static const int COOLING_TICKS = 900;

WallNutSeed::WallNutSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_WALLNUT, ObjectOnHands::WALL_NUT_SEED, COOLING_TICKS, COST, x) {}
