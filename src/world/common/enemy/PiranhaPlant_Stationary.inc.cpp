#include "PiranhaPlant.hpp"

NpcSettings NpcSettings_PiranhaPlant_Stationary = {
    .height = 32,
    .radius = 26,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_PIRANHA_PLANT,
};
