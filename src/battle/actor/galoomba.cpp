#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/Galoomba.h"

namespace galoomba {

extern EvtScript EVS_Init;
extern EvtScript EVS_Idle;
extern EvtScript EVS_TakeTurn;
extern EvtScript EVS_HandleEvent;
extern EvtScript EVS_Attack_Headbonk;
extern s32 DefaultAnims[];

// Actor Stats
constexpr s32 hp = 4;
constexpr s32 dmgHeadbonk = 1;

enum ActorPartIDs {
    PRT_MAIN            = 1,
};

enum ActorVars {
    AVAR_IsFlipped     = 0,
    AVAR_FlippedTurns  = 1,
};

s32 DefenseTable[] = {
    ELEMENT_NORMAL,   1,
    ELEMENT_END,
};

s32 StatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,              75,
    STATUS_KEY_POISON,             75,
    STATUS_KEY_FROZEN,            100,
    STATUS_KEY_DIZZY,              75,
    STATUS_KEY_UNUSED,            100,
    STATUS_KEY_STATIC,             75,
    STATUS_KEY_PARALYZE,           75,
    STATUS_KEY_SHRINK,             75,
    STATUS_KEY_STOP,              100,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,          0,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,          0,
    STATUS_TURN_MOD_UNUSED,         0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       0,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,           0,
    STATUS_END,
};

s32 FlippedDefense[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_END,
};

s32 FlippedStatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,             100,
    STATUS_KEY_POISON,            100,
    STATUS_KEY_FROZEN,            100,
    STATUS_KEY_DIZZY,             100,
    STATUS_KEY_UNUSED,            100,
    STATUS_KEY_STATIC,            100,
    STATUS_KEY_PARALYZE,          100,
    STATUS_KEY_SHRINK,            100,
    STATUS_KEY_STOP,              100,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,          0,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,          0,
    STATUS_TURN_MOD_UNUSED,         0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       0,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,           0,
    STATUS_END,
};

ActorPartBlueprint ActorParts[] = {
    {
        .flags = ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = DefaultAnims,
        .defenseTable = DefenseTable,
        .eventFlags = ACTOR_EVENT_FLAG_FLIPABLE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
};

extern "C" export ActorBlueprint blueprint = {
    .flags = 0,
    .maxHP = hp,
    .type = ACTOR_TYPE_GALOOMBA,
    .level = ACTOR_LEVEL_GALOOMBA,
    .partCount = ARRAY_COUNT(ActorParts),
    .partsData = ActorParts,
    .initScript = &EVS_Init,
    .statusTable = StatusTable,
    .escapeChance = 90,
    .airLiftChance = 100,
    .hurricaneChance = 90,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 DefaultAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Galoomba_Idle,
    STATUS_KEY_STONE,     ANIM_Galoomba_Still,
    STATUS_KEY_SLEEP,     ANIM_Galoomba_Sleep,
    STATUS_KEY_POISON,    ANIM_Galoomba_Idle,
    STATUS_KEY_STOP,      ANIM_Galoomba_Still,
    STATUS_KEY_STATIC,    ANIM_Galoomba_Idle,
    STATUS_KEY_PARALYZE,  ANIM_Galoomba_Still,
    STATUS_KEY_DIZZY,     ANIM_Galoomba_Dizzy,
    STATUS_KEY_UNUSED,    ANIM_Galoomba_Dizzy,
    STATUS_KEY_FROZEN,    ANIM_Galoomba_Still,
    STATUS_END,
};

// while shuffling around during idle
s32 ShuffleAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Galoomba_Run,
    STATUS_KEY_STONE,     ANIM_Galoomba_Still,
    STATUS_KEY_SLEEP,     ANIM_Galoomba_Sleep,
    STATUS_KEY_POISON,    ANIM_Galoomba_Idle,
    STATUS_KEY_STOP,      ANIM_Galoomba_Still,
    STATUS_KEY_STATIC,    ANIM_Galoomba_Run,
    STATUS_KEY_PARALYZE,  ANIM_Galoomba_Still,
    STATUS_KEY_DIZZY,     ANIM_Galoomba_Dizzy,
    STATUS_KEY_UNUSED,    ANIM_Galoomba_Dizzy,
    STATUS_KEY_FROZEN,    ANIM_Galoomba_Still,
    STATUS_END,
};

s32 FlippedAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Galoomba_ToppleIdle,
    STATUS_KEY_STONE,     ANIM_Galoomba_ToppleStill,
    STATUS_KEY_SLEEP,     ANIM_Galoomba_ToppleSleep,
    STATUS_KEY_POISON,    ANIM_Galoomba_ToppleIdle,
    STATUS_KEY_STOP,      ANIM_Galoomba_ToppleStill,
    STATUS_KEY_STATIC,    ANIM_Galoomba_ToppleIdle,
    STATUS_KEY_PARALYZE,  ANIM_Galoomba_ToppleStill,
    STATUS_KEY_DIZZY,     ANIM_Galoomba_ToppleDizzy,
    STATUS_KEY_UNUSED,    ANIM_Galoomba_ToppleIdle,
    STATUS_END,
};

EvtScript EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, AVAR_IsFlipped, false)
    Call(SetActorScale, ACTOR_SELF, Float(1.15), Float(1.15), Float(1.0))
    Return
    End
};

EvtScript EVS_Idle = {
    Label(10)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Loop(0)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
            Call(GetStatusFlags, ACTOR_SELF, LVar1)
            IfEq(LVar0, 0)
                IfNotFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(DefaultAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(FlippedAnims))
    EndSwitch
    Loop(20)
        Loop(0)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
            Call(GetStatusFlags, ACTOR_SELF, LVar1)
            IfEq(LVar0, 0)
                IfNotFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(DefaultAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(FlippedAnims))
    EndSwitch
    Loop(20)
        Loop(0)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
            Call(GetStatusFlags, ACTOR_SELF, LVar1)
            IfEq(LVar0, 0)
                IfNotFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    BreakLoop
                EndIf
            EndIf
            Wait(1)
        EndLoop
        Wait(1)
    EndLoop
    Goto(10)
    Return
    End
};

s32 FlipPosOffsets[] = {
    9, 16, 22, 26, 30, 32, 33,
    32, 30, 26, 22, 16, 9,
    0, 4, 6, 7, 6, 4, 0, 2, 0
};

EvtScript EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetActorScale, ACTOR_SELF, Float(1.15), Float(1.15), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(EVENT_HIT_COMBO)
        CaseOrEq(EVENT_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Hurt)
            ExecWait(EVS_Enemy_Hit)
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Burn)
            SetConst(LVar2, ANIM_Galoomba_BurnStill)
            ExecWait(EVS_Enemy_BurnHit)
        CaseEq(EVENT_BURN_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Burn)
            SetConst(LVar2, ANIM_Galoomba_BurnStill)
            ExecWait(EVS_Enemy_BurnHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_BurnStill)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_HurtStill)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_FLIP_TRIGGER)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
            IfEq(LVar0, false)
                Call(SetActorVar, ACTOR_SELF, AVAR_IsFlipped, true)
                Call(SetActorVar, ACTOR_SELF, AVAR_FlippedTurns, 1)
                Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(FlippedDefense))
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(FlippedAnims))
                Call(SetStatusTable, ACTOR_SELF, Ref(FlippedStatusTable))
                Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 0)
                Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLIPPED, true)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Hurt)
                Call(GetStatusFlags, ACTOR_SELF, LVarA)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                UseBuf(Ref(FlipPosOffsets))
                Set(LVarA, 0)
                // Loop(ARRAY_COUNT(FlipPosOffsets))
                Loop(12)
                    BufRead1(LVar0)
                    Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                    Sub(LVarA, 15)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVarA)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -180)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_ToppleIdle)
            Else
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -180)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Hurt)
                Wait(8)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_ToppleIdle)
            EndIf
        CaseEq(EVENT_SHOCK_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_BurnStill)
            ExecWait(EVS_Enemy_ShockHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Hurt)
            ExecWait(EVS_Enemy_Knockback)
            Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Dizzy)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, false)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.6))
            Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
        CaseEq(EVENT_SHOCK_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_BurnStill)
            ExecWait(EVS_Enemy_ShockHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_HurtStill)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_STAR_BEAM)
            // do nothing
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
            IfEq(LVar0, false)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Galoomba_Impact)
                ExecWait(EVS_Enemy_NoDamageHit)
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, STATUS_FLAGS_IMMOBILIZED)
                    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
                    Wait(10)
                EndIf
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Galoomba_ToppleIdle)
                ExecWait(EVS_Enemy_NoDamageHit)
            EndIf
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Hurt)
            ExecWait(EVS_Enemy_Hit)
            Wait(10)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_HurtStill)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_END_FIRST_STRIKE)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Run)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, false)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(EVENT_RECOVER_STATUS)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Idle)
            ExecWait(EVS_Enemy_Recover)
        CaseEq(EVENT_SCARE_AWAY)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Run)
            SetConst(LVar2, ANIM_Galoomba_Hurt)
            ExecWait(EVS_Enemy_ScareAway)
            Return
        CaseEq(EVENT_BEGIN_AIR_LIFT)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
            IfEq(LVar0, false)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Galoomba_Run)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Galoomba_ToppleIdle)
            EndIf
            ExecWait(EVS_Enemy_AirLift)
        CaseEq(EVENT_AIR_LIFT_FAILED)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
            IfEq(LVar0, false)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Galoomba_Run)
                ExecWait(EVS_Enemy_NoDamageHit)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Galoomba_ToppleIdle)
                ExecWait(EVS_Enemy_NoDamageHit)
            EndIf
        CaseEq(EVENT_BLOW_AWAY)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Galoomba_Hurt)
            ExecWait(EVS_Enemy_BlowAway)
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_IsFlipped, LVar0)
    IfEq(LVar0, true)
        Call(GetActorVar, ACTOR_SELF, AVAR_FlippedTurns, LVar0)
        Sub(LVar0, 1)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, AVAR_FlippedTurns, LVar0)
            Call(AddActorDecoration, ACTOR_SELF, PRT_MAIN, 0, ACTOR_DECORATION_SWEAT)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(3.0))
            Wait(30)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
            Call(RemoveActorDecoration, ACTOR_SELF, PRT_MAIN, 0)
        Else
            Call(AddActorDecoration, ACTOR_SELF, PRT_MAIN, 0, ACTOR_DECORATION_SWEAT)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(3.0))
            Wait(20)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
            Call(RemoveActorDecoration, ACTOR_SELF, PRT_MAIN, 0)
            Call(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP, SOUND_NONE, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_ACTOR_JUMP)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_ToppleIdle)
            Set(LVar0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            ChildThread
                Loop(5)
                    Add(LVar0, 15)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndChildThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(JumpToGoal, ACTOR_SELF, 8, false, true, false)
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_ACTOR_STEP_A)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
            Call(SetActorVar, ACTOR_SELF, AVAR_IsFlipped, false)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(DefaultAnims))
            Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(DefenseTable))
            Call(SetStatusTable, ACTOR_SELF, Ref(StatusTable))
            Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLIPPED, false)
            Call(ResetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP)
            Wait(5)
            ExecWait(EVS_Attack_Headbonk)
        EndIf
    Else
        ExecWait(EVS_Attack_Headbonk)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

#include "common/CalculateArcsinDeg.inc.c"

EvtScript EVS_Attack_Headbonk = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(UseBattleCamPreset, BTL_CAM_ENEMY_APPROACH)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, BTL_CAM_YADJ_TARGET, BTL_CAM_XADJ_AVG, false)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Run)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, false)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Jump)

    // // number of bonks
    // IfGe(GB_StoryProgress, STORY_)
    //     Set(LVarA, 2)
    // Else
    //     Set(LVarA, 1)
    // EndIf

    Label(0) // start of bonk
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(N(CalculateArcsinDeg), LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Jump)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, false, true, false)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Sleep)
            Call(SetActorScale, ACTOR_SELF, Float(1.25), Float(0.95), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.45), Float(0.65), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.15), Float(1.15), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Hurt)
            Wait(5)
            IfEq(LVarA, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Jump)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Jump)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, false, true, false)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Dizzy)
            Wait(5)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, PRT_MAIN, 0, ACTOR_DECORATION_SWEAT)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, false)
            Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.6))
            Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
            Call(RemoveActorDecoration, ACTOR_SELF, PRT_MAIN, 0)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, true)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(N(CalculateArcsinDeg), LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Jump)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, false, true, false)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Impact)
            Call(SetActorScale, ACTOR_SELF, Float(1.25), Float(0.95), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.45), Float(0.65), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, dmgHeadbonk, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
        Call(SetActorScale, ACTOR_SELF, Float(1.25), Float(0.95), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.15), Float(1.15), Float(1.0))
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)

        // rebonk if we have any more hits left
        // Sub(LVarA, 1)
        // IfGt(LVarA, 0)
        //    Goto(0)
        // EndIf

        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 40)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.8))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, false, true, false)
        Add(LVar0, 30)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 8, false, true, false)
        Add(LVar0, 20)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 6, false, true, false)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Idle)
        Wait(3)
        Call(YieldTurn)
        Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(2.0))
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Galoomba_Run)
        Call(SetGoalToHome, ACTOR_SELF)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(RunToGoal, ACTOR_SELF, 0, false)
        Call(SetAnimationRate, ACTOR_SELF, PRT_MAIN, Float(1.0))
    EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

}; // namespace galoomba
