#include "Seeds.hpp"

RepeaterSeed::RepeaterSeed(int x, pGameWorld belonging_world)
    : SeedBase(belonging_world, IMGID_SEED_WALLNUT, ObjectOnHands::REPEATER_SEED, 240, 200, x) {}
