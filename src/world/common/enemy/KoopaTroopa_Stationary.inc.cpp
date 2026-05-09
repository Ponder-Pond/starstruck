#include "KoopaTroopa.h"

NpcSettings NpcSettings_KoopaTroopa_Stationary = {
    .height = 35,
    .radius = 24,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_KOOPA_TROOPA,
};
