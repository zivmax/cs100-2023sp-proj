#include "Seeds.hpp"

static const int COST = 200;
static const int COOLING_TICKS = 240;

RepeaterSeed::RepeaterSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_REPEATER, ObjectOnHands::REPEATER_SEED, COOLING_TICKS, COST, x) {}


