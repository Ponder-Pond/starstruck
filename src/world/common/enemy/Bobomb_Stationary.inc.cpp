#include "common.h"
#include "Bobomb.h"

NpcSettings NpcSettings_Bobomb_Stationary = {
    .height = 23,
    .radius = 20,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_BOB_OMB,
};
