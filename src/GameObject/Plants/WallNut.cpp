#include "Plants.hpp"

WallNut::WallNut(int x, int y, pGameWorld belonging_world)
    : PlantBase(belonging_world, IMGID_WALLNUT, ANIMID_IDLE_ANIM, 4000, x, y) {}