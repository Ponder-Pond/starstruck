#include "isk_20.h"

namespace isk_20 {

#include "world/common/enemy/Goomba_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_Goomba = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_Goomba_Run)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Goomba_Dizzy)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_Goomba = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Goomba = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Goomba))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Goomba))
    Return
    End
};

NpcData NpcData_Goomba = {
    .id = NPC_Goomba,
    .settings = &NpcSettings_Goomba_Stationary,
    .pos = { GEN_GOOMBA_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_Goomba,
    .yaw = GEN_GOOMBA_DIR,
    .drops = NO_DROPS,
    .animations = GOOMBA_ANIMS,
};

#include "world/common/enemy/SpikedGoomba_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_SpikedGoomba = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Run)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Laugh)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_SpikedGoomba = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_SpikedGoomba = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_SpikedGoomba))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_SpikedGoomba))
    Return
    End
};

NpcData NpcData_SpikedGoomba = {
    .id = NPC_SpikedGoomba,
    .settings = &NpcSettings_SpikedGoomba_Stationary,
    .pos = { GEN_SPIKED_GOOMBA_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_SpikedGoomba,
    .yaw = GEN_SPIKED_GOOMBA_DIR,
    .drops = NO_DROPS,
    .animations = SPIKED_GOOMBA_ANIMS,
};

#include "world/common/enemy/KoopaTroopa_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_KoopaTroopa = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_KoopaTroopa_Run)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_KoopaTroopa_ShellSpin)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_KoopaTroopa = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_KoopaTroopa = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_KoopaTroopa))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_KoopaTroopa))
    Return
    End
};

NpcData NpcData_KoopaTroopa = {
    .id = NPC_KoopaTroopa,
    .settings = &NpcSettings_KoopaTroopa_Stationary,
    .pos = { GEN_KOOPA_TROOPA_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_KoopaTroopa,
    .yaw = GEN_KOOPA_TROOPA_DIR,
    .drops = KOOPA_TROOPA_NOK_DROPS,
    .animations = KOOPA_TROOPA_ANIMS,
};

#include "world/common/enemy/Bobomb_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_Bobomb = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_Bobomb_Run)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Bobomb_AngryChase)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_Bobomb = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Bobomb = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Bobomb))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Bobomb))
    Return
    End
};

NpcData NpcData_Bobomb = {
    .id = NPC_Bobomb,
    .settings = &NpcSettings_Bobomb_Stationary,
    .pos = { GEN_BOBOMB_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_Bobomb,
    .yaw = GEN_BOBOMB_DIR,
    .drops = NO_DROPS,
    .animations = BOBOMB_ANIMS,
};

#include "world/common/enemy/Cleft_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_Cleft = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_Cleft_Anim07)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Cleft_Anim11)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_Cleft = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Cleft = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Cleft))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Cleft))
    Return
    End
};

NpcData NpcData_Cleft = {
    .id = NPC_Cleft,
    .settings = &NpcSettings_Cleft_Stationary,
    .pos = { GEN_CLEFT_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_Cleft,
    .yaw = GEN_CLEFT_DIR,
    .drops = NO_DROPS,
    .animations = CLEFT_ANIMS,
};

#include "world/common/enemy/Bandit_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_Bandit = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_Bandit_Run)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Bandit_Laugh)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_Bandit = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Bandit = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Bandit))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Bandit))
    Return
    End
};

NpcData NpcData_Bandit = {
    .id = NPC_Bandit,
    .settings = &NpcSettings_Bandit_Stationary,
    .pos = { GEN_BANDIT_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_Bandit,
    .yaw = GEN_BANDIT_DIR,
    .drops = NO_DROPS,
    .animations = BANDIT_ANIMS,
};

#include "world/common/enemy/Pokey_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_Pokey = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_Pokey_Run4)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Pokey_Run4)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_Pokey = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Pokey = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Pokey))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Pokey))
    Return
    End
};

NpcData NpcData_Pokey = {
    .id = NPC_Pokey,
    .settings = &NpcSettings_Pokey_Stationary,
    .pos = { GEN_POKEY_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_Pokey,
    .yaw = GEN_POKEY_DIR,
    .drops = NO_DROPS,
    .animations = POKEY_ANIMS,
};

#include "world/common/enemy/SpikeTop_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_BuzzyBeetle = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_BuzzyBeetle_Anim04)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_BuzzyBeetle_Anim05)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_BuzzyBeetle = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_BuzzyBeetle = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_BuzzyBeetle))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_BuzzyBeetle))
    Return
    End
};

NpcData NpcData_BuzzyBeetle = {
    .id = NPC_BuzzyBeetle,
    .settings = &NpcSettings_BuzzyBeetle_Stationary,
    .pos = { GEN_BUZZY_BEETLE_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_BuzzyBeetle,
    .yaw = GEN_BUZZY_BEETLE_DIR,
    .drops = NO_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

#include "world/common/enemy/PiranhaPlant_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_PiranhaPlant = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_X, -930, GEN_ENEMY_ENTER_POS_Z)
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_BATTLE_POS_VEC)
    Call(SetNpcAnimation, NPC_SELF, ANIM_SmallPiranha_Anim03)
    Wait(5)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_SmallPiranha_Anim07)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_PiranhaPlant = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_PiranhaPlant = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_PiranhaPlant))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_PiranhaPlant))
    Return
    End
};

NpcData NpcData_PiranhaPlant = {
    .id = NPC_PiranhaPlant,
    .settings = &NpcSettings_PiranhaPlant_Stationary,
    .pos = { GEN_PIRANHA_PLANT_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_PiranhaPlant,
    .yaw = GEN_PIRANHA_PLANT_DIR,
    .drops = NO_DROPS,
    .animations = PIRANHA_PLANT_ANIMS,
};

#include "world/common/enemy/Clubba_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_Clubba = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Anim04)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Anim10)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_Clubba = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Clubba = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Clubba))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Clubba))
    Return
    End
};

NpcData NpcData_Clubba = {
    .id = NPC_Clubba,
    .settings = &NpcSettings_Clubba_Stationary,
    .pos = { GEN_CLUBBA_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_Clubba,
    .yaw = GEN_CLUBBA_DIR,
    .drops = NO_DROPS,
    .animations = CLUBBA_ANIMS,
};

#include "world/common/enemy/ShyGuy_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_ShyGuy = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_ShyGuy_Red_Anim03)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_ShyGuy_Red_Anim04)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_ShyGuy = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_ShyGuy = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_ShyGuy))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_ShyGuy))
    Return
    End
};

NpcData NpcData_ShyGuy = {
    .id = NPC_ShyGuy,
    .settings = &NpcSettings_ShyGuy_Stationary,
    .pos = { GEN_SHY_GUY_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_ShyGuy,
    .yaw = GEN_SHY_GUY_DIR,
    .drops = NO_DROPS,
    .animations = RED_SHY_GUY_ANIMS,
};

#include "world/common/enemy/SpearGuy_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_SpearGuy = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpearGuy_Anim06)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpearGuy_Anim0E)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_SpearGuy = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_SpearGuy = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_SpearGuy))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_SpearGuy))
    Return
    End
};

NpcData NpcData_SpearGuy = {
    .id = NPC_SpearGuy,
    .settings = &NpcSettings_SpearGuy_Stationary,
    .pos = { GEN_SPEAR_GUY_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_SpearGuy,
    .yaw = GEN_SPEAR_GUY_DIR,
    .drops = NO_DROPS,
    .animations = SPEAR_GUY_ANIMS,
};

EvtScript EVS_NpcIdle_SpikeTop = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikeTop_Anim08)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_SpikeTop_Anim0A)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_SpikeTop = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_SpikeTop = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_SpikeTop))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_SpikeTop))
    Return
    End
};

NpcData NpcData_SpikeTop = {
    .id = NPC_SpikeTop,
    .settings = &NpcSettings_SpikeTop_Stationary,
    .pos = { GEN_SPIKE_TOP_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_SpikeTop,
    .yaw = GEN_SPIKE_TOP_DIR,
    .drops = NO_DROPS,
    .animations = SPIKE_TOP_ANIMS,
};

EvtScript EVS_NpcIdle_BonyBeetle = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_BonyBeetle_Anim0F)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_BonyBeetle_Anim17)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_BonyBeetle = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_BonyBeetle = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_BonyBeetle))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_BonyBeetle))
    Return
    End
};

NpcData NpcData_BonyBeetle = {
    .id = NPC_BonyBeetle,
    .settings = &NpcSettings_BonyBeetle_Stationary,
    .pos = { GEN_BONY_BEETLE_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_BonyBeetle,
    .yaw = GEN_BONY_BEETLE_DIR,
    .drops = NO_DROPS,
    .animations = BONY_BEETLE_ANIMS,
};

#include "world/common/enemy/HammerBros_Stationary.inc.cpp"

EvtScript EVS_NpcIdle_HammerBros = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Wait(1)
        IfEq(LVar0, true)
            Goto(0)
        EndIf
    Call(SetNpcPos, NPC_SELF, GEN_ENEMY_ENTER_POS_VEC)
    Wait(5)
    Call(SetNpcSpeed, NPC_SELF, Float(5.0))
    Call(SetNpcAnimation, NPC_SELF, ANIM_HammerBros_Anim07)
    Call(NpcMoveTo, NPC_SELF, GEN_ENEMY_BATTLE_POS_X, GEN_ENEMY_BATTLE_POS_Z, 0)
    ExecWait(EVS_CloseRightGate)
    Call(SetNpcAnimation, NPC_SELF, ANIM_HammerBros_Anim18)
    Wait(30)
    Call(StartBossBattle, SONG_SPECIAL_BATTLE)
    Return
    End
};

EvtScript EVS_NpcDefeat_HammerBros = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            IfFlag(MF_GauntletDefeated, false)
                Exec(EVS_OpenRightGate)
            EndIf
            Call(DoNpcDefeatSpecial)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_HammerBros = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_HammerBros))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_HammerBros))
    Return
    End
};

NpcData NpcData_HammerBros = {
    .id = NPC_HammerBros,
    .settings = &NpcSettings_HammerBros_Stationary,
    .pos = { GEN_HAMMER_BROS_VEC },
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_DELAY_AFTER_FLEE,
    .init = &EVS_NpcInit_HammerBros,
    .yaw = GEN_HAMMER_BROS_DIR,
    .drops = NO_DROPS,
    .animations = HAMMER_BROS_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Goomba, BTL_TST_FORMATION_0, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_SpikedGoomba, BTL_TST_FORMATION_1, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_KoopaTroopa, BTL_TST_FORMATION_2, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_Bobomb, BTL_TST_FORMATION_3, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_Cleft, BTL_TST_FORMATION_4, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_Bandit, BTL_TST_FORMATION_5, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_Pokey, BTL_TST_FORMATION_6, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_BuzzyBeetle, BTL_TST_FORMATION_7, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_PiranhaPlant, BTL_TST_FORMATION_8, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_Clubba, BTL_TST_FORMATION_9, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_ShyGuy, BTL_TST_FORMATION_10, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_SpearGuy, BTL_TST_FORMATION_11, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_SpikeTop, BTL_TST_FORMATION_12, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_BonyBeetle, BTL_TST_FORMATION_13, BTL_TST_STAGE_0),
    NPC_GROUP(NpcData_HammerBros, BTL_TST_FORMATION_14, BTL_TST_STAGE_0),
    {}
};

} // namespace isk_20
