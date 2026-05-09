#include "isk_20.h"
#include "sprite/player.h"

namespace isk_20 {

EntryList Entrances = { GEN_ENTRY_LIST };

EvtScript EVS_ExitWalk_isk_19_1 = EVT_EXIT_WALK(40, isk_16_ENTRY_0, "isk_19", isk_19_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_isk_19_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Exec(EVS_OpenLeftGate)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_ISK_16)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_SetupFlames)
    Call(SetMusic, 0, SONG_DRY_DRY_RUINS, 0, VOL_LEVEL_FULL)
    Exec(EVS_EnterMap)
    Return
    End
};

} // namespace isk_20

extern "C" export MapSettings isk_20_settings = {
    .main = &isk_20::EVS_Main,
    .entryList = &isk_20::Entrances,
    .entryCount = ENTRY_COUNT(isk_20::Entrances),
    .tattle = { MSG_MapTattle_isk_16 },
    .sfxReverb = 2,
};
