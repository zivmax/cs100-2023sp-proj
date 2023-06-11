#include "Seeds.hpp"

static const int COST = 100;
static const int COOLING_TICKS = 240;

PeaShooterSeed::PeaShooterSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_PEASHOOTER, ObjectOnHands::PEA_SHOOTER_SEED, COOLING_TICKS, COST, x) {}

