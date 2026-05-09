#include "SpikedGoomba.h"

NpcSettings NpcSettings_SpikedGoomba_Stationary = {
    .height = 23,
    .radius = 23,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_SPIKED_GOOMBA,
};
