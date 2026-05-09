#include "ShyGuy.h"

NpcSettings NpcSettings_ShyGuy_Stationary = {
    .height = 23,
    .radius = 22,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_SHY_GUY,
};
