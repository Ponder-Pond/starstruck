
#include "Bandit.h"

NpcSettings NpcSettings_Bandit_Stationary = {
    .height = 26,
    .radius = 24,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_BANDIT,
};
