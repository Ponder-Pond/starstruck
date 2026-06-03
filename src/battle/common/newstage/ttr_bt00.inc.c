#include "common.h"
#include "effects.h"
#include "model.h"
#include "battle/battle.h"
#include "mapfs/ttr_bt00_shape.h"
#include "mapfs/ttr_bt00_hit.h"

// namespace ttr_00 {

// EvtScript EVS_PreBattle = {
//     Call(SetSpriteShading, SHADING_NONE)
//     Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
//     Return
//     End
// };

// EvtScript EVS_PostBattle = {
//     Return
//     End
// };

// } // namespace ttr_00

// Stage Theater = {
//     .texture = "ttr_tex",
//     .shape = "ttr_bt00_shape",
//     .hit = "ttr_bt00_hit",
//     .preBattle = &ttr_00::EVS_PreBattle,
//     .postBattle = &ttr_00::EVS_PostBattle,
// };

// extern "C" Stage Theater;

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
};

Stage A(ttr_bt00) = {
    .texture = "ttr_tex",
    .shape = "ttr_bt00_shape",
    .hit = "ttr_bt00_hit",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};
