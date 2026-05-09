#include "isk_20.h"
#include "sprite/player.h"

namespace isk_20 {

EvtScript EVS_OpenLeftGate = {
    Call(DisablePlayerInput, true)
    Call(SetPlayerPos, GEN_MARIO_ENTER_POS_VEC)

    Set(LVarD, 0)

    Call(ShakeCam, CAM_DEFAULT, 0, 1, Float(0.5))
    Wait(1)
    Call(PlaySound, SOUND_LARGE_GATE_OPEN)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_LeftGate, COLLIDER_FLAGS_UPPER_MASK)

    Label(10)
    Call(TranslateModel, MODEL_LeftGate, 0, LVarD, 0)
    Add(LVarD, 2)

    Wait(1)
    IfLt(LVarD, 60)
        Goto(10)
    EndIf
    Call(StopSound, SOUND_LARGE_GATE_OPEN)
    Wait(10)
    Call(SetPlayerSpeed, 5)
    Call(PlayerMoveTo, GEN_MARIO_BATTLE_POS_X, GEN_MARIO_BATTLE_POS_Z, 0)
    Wait(15)
    // close the gate
    Exec(EVS_CloseLeftGate)

    Return
    End
};

EvtScript EVS_CloseLeftGate = {
    Set(LVarD, 60)

    Call(PlaySound, SOUND_LARGE_GATE_OPEN)
    Label(10)
    Call(TranslateModel, MODEL_LeftGate, 0, LVarD, 0)
    Sub(LVarD, 2)

    Wait(1)
    IfGt(LVarD, 0)
        Goto(10)
    EndIf

    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_LeftGate, COLLIDER_FLAGS_UPPER_MASK)
    Call(StopSound, SOUND_LARGE_GATE_OPEN)
    Call(PlaySound, SOUND_LARGE_GATE_CLOSE)
    Call(ShakeCam, CAM_BATTLE, 0, 4, Float(0.5))
    Wait(30)
    Exec(EVS_OpenRightGate)
    Return
    End
};

EvtScript EVS_OpenRightGate = {
    Call(DisablePlayerInput, true)
    Wait(15)

    Set(LVarD, 0)

    Call(ShakeCam, CAM_DEFAULT, 0, 1, Float(0.5))
    Wait(1)
    Call(PlaySound, SOUND_LARGE_GATE_OPEN)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_LeftGate, COLLIDER_FLAGS_UPPER_MASK)

    Label(10)
    Call(TranslateModel, MODEL_LeftGate, 0, LVarD, 0)
    Add(LVarD, 2)

    Wait(1)
    IfLt(LVarD, 60)
        Goto(10)
    EndIf
    Call(StopSound, SOUND_LARGE_GATE_OPEN)
    Wait(10)
    ExecWait(EVS_GauntletRandomizer)

    Return
    End
};

EvtScript EVS_CloseRightGate = {
    Set(LVarD, 60)

    Call(PlaySound, SOUND_LARGE_GATE_OPEN)
    Label(10)
    Call(TranslateModel, MODEL_LeftGate, 0, LVarD, 0)
    Sub(LVarD, 2)

    Wait(1)
    IfGt(LVarD, 0)
        Goto(10)
    EndIf

    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_LeftGate, COLLIDER_FLAGS_UPPER_MASK)
    Call(StopSound, SOUND_LARGE_GATE_OPEN)
    Call(PlaySound, SOUND_LARGE_GATE_CLOSE)
    Call(ShakeCam, CAM_BATTLE, 0, 4, Float(0.5))
    Wait(30)
    Return
    End
};

} // namespace isk_20
