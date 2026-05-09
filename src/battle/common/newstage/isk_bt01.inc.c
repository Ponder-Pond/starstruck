#include "common.h"
#include "effects.h"
#include "model.h"
#include "battle/battle.h"
#include "mapfs/isk_bt01_shape.h"

// namespace battle::area::tst {

// namespace isk_01 {

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

// } // namespace isk_01

Stage A(DryDryRuins) = {
    .texture = "isk_tex",
    .shape = "isk_bt01_shape",
    .hit = "isk_bt01_hit",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};

extern Stage A(DryDryRuins);

// } // namespace battle::area::tst
