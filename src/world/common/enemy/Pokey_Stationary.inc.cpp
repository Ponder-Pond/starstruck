#include "Pokey.h"

NpcSettings NpcSettings_Pokey_Stationary = {
    .height = 72,
    .radius = 15,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_POKEY,
};
