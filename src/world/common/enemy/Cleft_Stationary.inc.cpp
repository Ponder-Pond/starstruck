#include "Cleft.h"

NpcSettings NpcSettings_Cleft_Stationary = {
    .height = 26,
    .radius = 24,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_CLEFT,
};
