#include "Seeds.hpp"

static const int COST = 50;
static const int COOLING_TICKS = 240;

SunFlowerSeed::SunFlowerSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_SUNFLOWER, ObjectOnHands::SUN_FLOWER_SEED, COOLING_TICKS, COST, x) {}

