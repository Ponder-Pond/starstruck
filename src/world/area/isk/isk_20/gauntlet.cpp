#include "isk_20.h"

namespace isk_20 {

#define TOTAL_ARENA_NPCS 15
#define MAX_GAUNTLET_BATTLES 5

s32 gGauntletRemaining = 5;
s32 gLastArenaNPC = -1;

API_CALLABLE(ResetArenaGauntlet) {
    gGauntletRemaining = 5;
    gLastArenaNPC = -1;

    return ApiStatus_DONE2;
}

typedef struct {
    s32 npcID;
    b32 used;
} ArenaNPC;

ArenaNPC gArenaNPCs[TOTAL_ARENA_NPCS] = {
    { NPC_Goomba, false },
    { NPC_SpikedGoomba, false },
    { NPC_KoopaTroopa, false },
    { NPC_Bobomb, false },
    { NPC_Cleft, false },
    { NPC_Bandit, false },
    { NPC_Pokey, false },
    { NPC_BuzzyBeetle, false },
    { NPC_PiranhaPlant, false },
    { NPC_Clubba, false },
    { NPC_ShyGuy, false },
    { NPC_SpearGuy, false },
    { NPC_SpikeTop, false },
    { NPC_BonyBeetle, false },
    { NPC_HammerBros, false },
};


API_CALLABLE(GetRandomArenaNPC) {
    s32 index;

    if (gGauntletRemaining <= 0) {
        evt_set_variable(script, LVar0, -1);
        return ApiStatus_DONE2;
    }

    while (true) {
        index = rand_int(14);

        // prevent immediate repeat only (optional)
        if (gArenaNPCs[index].npcID == gLastArenaNPC) {
            continue;
        }

        gLastArenaNPC = gArenaNPCs[index].npcID;

        gGauntletRemaining--;

        evt_set_variable(script, LVar0,
            gArenaNPCs[index].npcID);

        break;
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_GauntletRandomizer = {
    Call(GetRandomArenaNPC)

    IfEq(LVar0, -1)
        Set(MF_GauntletDefeated, true)
        Return
    EndIf

    Call(SetNpcVar, LVar0, 0, true)
    Return
    End
};

} // namespace isk_20
