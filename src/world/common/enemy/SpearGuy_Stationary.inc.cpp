#include "SpearGuy.hpp"

AnimID ExtraAnims_SpearGuy[] = {
    ANIM_SpearGuy_Anim00,
    ANIM_SpearGuy_Anim03,
    ANIM_SpearGuy_Anim05,
    ANIM_SpearGuy_Anim06,
    ANIM_SpearGuy_Anim07,
    ANIM_SpearGuy_Anim0F,
    ANIM_SpearGuy_Anim10,
    ANIM_SpearGuy_Anim1A,
    ANIM_SpearGuy_Anim1B,
    ANIM_LIST_END
};

NpcSettings NpcSettings_SpearGuy_Stationary = {
    .height = 23,
    .radius = 22,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .level = ACTOR_LEVEL_SPEAR_GUY,
};
