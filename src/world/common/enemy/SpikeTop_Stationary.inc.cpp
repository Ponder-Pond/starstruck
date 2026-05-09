#include "SpikeTop.h"

NpcSettings NpcSettings_BuzzyBeetle_Stationary = {
    .height = 20,
    .radius = 22,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_BUZZY_BEETLE,
};

// NpcSettings NpcSettings_BuzzyBeetle_Ceiling = {
//     .height = 20,
//     .radius = 22,
//     .onHit = &EnemyNpcHit,
//     .onDefeat = &EnemyNpcDefeat,
//     .level = ACTOR_LEVEL_BUZZY_BEETLE,
// };

NpcSettings NpcSettings_SpikeTop_Stationary = {
    .height = 20,
    .radius = 22,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_SPIKE_TOP,
};

NpcSettings NpcSettings_BonyBeetle_Stationary = {
    .height = 24,
    .radius = 24,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_BONY_BEETLE,
};
