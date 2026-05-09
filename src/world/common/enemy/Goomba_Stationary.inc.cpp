#include "Goomba.h"

NpcSettings NpcSettings_Goomba_Stationary = {
    .height = 20,
    .radius = 23,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_GOOMBA,
};
