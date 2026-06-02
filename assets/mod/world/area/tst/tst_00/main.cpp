#include "tst_00.h"

namespace tst_00 {

EntryList Entrances = { GEN_ENTRY_LIST };

// #include "world/common/atomic/TexturePan.inc.c"

// EvtScript EVS_TexPan = {
//     Call(SetTexPanner, MODEL_Outside, TEX_PANNER_1)
//     Call(EnableTexPanning, MODEL_Outside, true)
//     Thread
//         GEN_TEX_PANNER_1
//         Exec(N(EVS_UpdateTexturePan))
//     EndThread
//     Return
//     End
// };

API_CALLABLE(MapTransition) {
    set_map_transition_effect(TRANSITION_BEGIN_OR_END_GAME);
    return ApiStatus_DONE2;
}

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(0)
            // Call(SetNpcPos, NPC_Bowser, 100, 0, 0)
            // Call(PlayerFaceNpc, NPC_Bowser, true)
            // Call(NpcFacePlayer, NPC_Bowser, 0)
            // Wait(1)
            Call(MapTransition)
            Exec(EVS_Scene_BeginGame)
        // CaseEq(1)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, GEN_MAP_LOCATION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    // Call(MakeNpcs, true, Ref(DefaultNPCs))
    Exec(EVS_EnterMap)
    // Exec(EVS_TexPan)
    Return
    End
};

} // namespace tst_00

extern "C" export s32 tst_00_map_init(void) {
    sprintf(wMapTexName, "tst_tex");
    return false;
}

extern "C" export MapSettings tst_00_settings = {
    .main = &tst_00::EVS_Main,
    .entryList = &tst_00::Entrances,
    .entryCount = ENTRY_COUNT(tst_00::Entrances),
    // .bgName = "kmr_bg",
    .tattle = { MSG_NONE }, //TODO add tattle message
};
