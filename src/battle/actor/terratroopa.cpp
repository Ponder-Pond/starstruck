#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/Terratroopa.h"

namespace terratroopa {

extern s32 DefaultAnims[];
extern EvtScript EVS_Init;
extern EvtScript EVS_Idle;
extern EvtScript EVS_TakeTurn;
extern EvtScript EVS_HandleEvent;
extern EvtScript EVS_Move_Hide;
extern EvtScript EVS_Attack_ShellToss;

enum ActorPartIDs {
    PRT_MAIN            = 1,
};

enum ActorVars {
    AVAR_IsHidden     = 0,
    AVAR_HiddenTurns  = 1,
};

// Actor Stats
constexpr s32 hp = 3;
constexpr s32 dmgShellToss = 2;

s32 NormalDefense[] = {
    ELEMENT_NORMAL,   1,
    ELEMENT_SMASH,    1,
    ELEMENT_JUMP,     1,
    ELEMENT_WATER,    1,
    ELEMENT_BLAST,    1,
    ELEMENT_END,
};

s32 HiddenDefense[] = {
    ELEMENT_NORMAL,   2,
    ELEMENT_END,
};

s32 StatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,              90,
    STATUS_KEY_POISON,             60,
    STATUS_KEY_FROZEN,            100,
    STATUS_KEY_DIZZY,              90,
    STATUS_KEY_UNUSED,                0,
    STATUS_KEY_STATIC,             80,
    STATUS_KEY_PARALYZE,           90,
    STATUS_KEY_SHRINK,             90,
    STATUS_KEY_STOP,              100,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,          0,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,          0,
    STATUS_TURN_MOD_UNUSED,           0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       1,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,           0,
    STATUS_END,
};

ActorPartBlueprint ActorParts[] = {
    {
        .flags = ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 15 },
        .opacity = 255,
        .idleAnimations = DefaultAnims,
        .defenseTable = NormalDefense,
        .eventFlags = ACTOR_EVENT_FLAG_FLIPABLE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
};

extern "C" export ActorBlueprint blueprint = {
    .flags = 0,
    .maxHP = hp,
    .type = ACTOR_TYPE_TERRATROOPA,
    .level = ACTOR_LEVEL_TERRATROOPA,
    .partCount = ARRAY_COUNT(ActorParts),
    .partsData = ActorParts,
    .initScript = &EVS_Init,
    .statusTable = StatusTable,
    .escapeChance = 70,
    .airLiftChance = 100,
    .hurricaneChance = 50,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 36, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { 32, 0 },
    .statusTextOffset = { 32, 0 },
};

s32 DefaultAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Terratroopa_Idle,
    STATUS_KEY_STONE,     ANIM_Terratroopa_Still,
    STATUS_KEY_SLEEP,     ANIM_Terratroopa_Sleep,
    STATUS_KEY_POISON,    ANIM_Terratroopa_Idle,
    STATUS_KEY_STOP,      ANIM_Terratroopa_Still,
    STATUS_KEY_STATIC,    ANIM_Terratroopa_Idle,
    STATUS_KEY_PARALYZE,  ANIM_Terratroopa_Still,
    STATUS_KEY_DIZZY,     ANIM_Terratroopa_Dizzy,
    STATUS_KEY_UNUSED,    ANIM_Terratroopa_Dizzy,
    STATUS_END,
};

s32 ShuffleAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Terratroopa_Walk,
    STATUS_KEY_STONE,     ANIM_Terratroopa_Still,
    STATUS_KEY_SLEEP,     ANIM_Terratroopa_Sleep,
    STATUS_KEY_POISON,    ANIM_Terratroopa_Walk,
    STATUS_KEY_STOP,      ANIM_Terratroopa_Still,
    STATUS_KEY_STATIC,    ANIM_Terratroopa_Walk,
    STATUS_KEY_PARALYZE,  ANIM_Terratroopa_Still,
    STATUS_KEY_DIZZY,     ANIM_Terratroopa_Dizzy,
    STATUS_KEY_UNUSED,    ANIM_Terratroopa_Dizzy,
    STATUS_END,
};

s32 HiddenAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Terratroopa_ShellIdle,
    STATUS_KEY_STONE,     ANIM_Terratroopa_ShellStill,
    STATUS_KEY_SLEEP,     ANIM_Terratroopa_ShellIdle,
    STATUS_KEY_POISON,    ANIM_Terratroopa_ShellIdle,
    STATUS_KEY_STOP,      ANIM_Terratroopa_ShellStill,
    STATUS_KEY_STATIC,    ANIM_Terratroopa_ShellIdle,
    STATUS_KEY_PARALYZE,  ANIM_Terratroopa_ShellStill,
    STATUS_KEY_DIZZY,     ANIM_Terratroopa_ShellIdle,
    STATUS_KEY_UNUSED,    ANIM_Terratroopa_ShellIdle,
    STATUS_END,
};

EvtScript EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, AVAR_IsHidden, false)
    Call(SetActorScale, ACTOR_SELF, Float(1.1), Float(1.1), Float(1.0))
    Return
    End
};

#include "common/battle/SetAbsoluteStatusOffsets.inc.c"

EvtScript EVS_UpdateTargetOffsets = {
    Switch(LVar0)
        CaseEq(0)
            IfFlag(LVar1, STATUS_FLAG_SLEEP | STATUS_FLAG_DIZZY)
                Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 15)
                Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 0)
                Call(N(SetAbsoluteStatusOffsets), -10, 20, 10, 20)
            Else
                Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 15)
                Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, -1, -4)
                Call(N(SetAbsoluteStatusOffsets), -15, 32, 5, 32)
            EndIf
        CaseEq(1)
            Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 0)
            Call(N(SetAbsoluteStatusOffsets), -10, 20, 10, 20)
    EndSwitch
    Return
    End
};

EvtScript EVS_Idle = {
    Label(0)
        Call(RandInt, 80, LVarA)
        Add(LVarA, 80)
        Loop(LVarA)
            Label(1)
                Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
                Call(GetStatusFlags, ACTOR_SELF, LVar1)
                ExecWait(EVS_UpdateTargetOffsets)
                IfEq(LVar0, 1)
                    Wait(1)
                    Goto(1)
                EndIf
                IfFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    Wait(1)
                    Goto(1)
                EndIf
            Wait(1)
        EndLoop
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 5)
        Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
        Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(ShuffleAnims))
        Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(IdleRunToGoal, ACTOR_SELF, 0)
        Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(DefaultAnims))
            CaseEq(1)
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(HiddenAnims))
        EndSwitch
        Loop(20)
            Label(2)
                Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
                Call(GetStatusFlags, ACTOR_SELF, LVar1)
                ExecWait(EVS_UpdateTargetOffsets)
                IfEq(LVar0, 1)
                    Wait(1)
                    Goto(2)
                EndIf
                IfFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    Wait(1)
                    Goto(2)
                EndIf
            Wait(1)
        EndLoop
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 5)
        Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
        Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(ShuffleAnims))
        Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(IdleRunToGoal, ACTOR_SELF, 0)
        Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(DefaultAnims))
            CaseEq(1)
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(HiddenAnims))
        EndSwitch
        Loop(80)
            Label(3)
                Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
                Call(GetStatusFlags, ACTOR_SELF, LVar1)
                ExecWait(EVS_UpdateTargetOffsets)
                IfEq(LVar0, 1)
                    Wait(1)
                    Goto(3)
                EndIf
                IfFlag(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    Wait(1)
                    Goto(3)
                EndIf
            Wait(1)
        EndLoop
        Goto(0)
    Return
    End
};

EvtScript EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.1), Float(1.1), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(EVENT_HIT_COMBO)
        CaseOrEq(EVENT_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_Hit)
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Burn)
            SetConst(LVar2, ANIM_Terratroopa_BurnStill)
            ExecWait(EVS_Enemy_BurnHit)
        CaseEq(EVENT_BURN_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Burn)
            SetConst(LVar2, ANIM_Terratroopa_BurnStill)
            ExecWait(EVS_Enemy_BurnHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_BurnStill)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_FLIP_TRIGGER)
            Call(SetActorVar, ACTOR_SELF, AVAR_IsHidden, true)
            Call(SetActorVar, ACTOR_SELF, AVAR_HiddenTurns, 2)
            Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(HiddenDefense))
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(HiddenAnims))
            Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 10)
            Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLIPPED, true)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Hurt)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellIn)
            Wait(17)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellIdle)
        CaseEq(EVENT_SHOCK_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_ShockHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_Knockback)
            Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Run)
            ExecWait(EVS_Enemy_ReturnHome)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.6))
            Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
        CaseEq(EVENT_SHOCK_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_ShockHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_ShellIn)
                ExecWait(EVS_Enemy_NoDamageHit)
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, STATUS_FLAGS_IMMOBILIZED)
                    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellOut)
                    Wait(10)
                EndIf
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_ShellIdle)
                ExecWait(EVS_Enemy_NoDamageHit)
            EndIf
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_Hit)
            Wait(10)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Hurt)
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_END_FIRST_STRIKE)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_Run)
                ExecWait(EVS_Enemy_ReturnHome)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(EVENT_RECOVER_STATUS)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_Idle)
                ExecWait(EVS_Enemy_Recover)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_ShellIdle)
                ExecWait(EVS_Enemy_NoDamageHit)
            EndIf
        CaseEq(EVENT_SCARE_AWAY)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_Run)
                SetConst(LVar2, ANIM_Terratroopa_Hurt)
                ExecWait(EVS_Enemy_ScareAway)
                Return
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_ShellIdle)
                ExecWait(EVS_Enemy_NoDamageHit)
            EndIf
        CaseEq(EVENT_BEGIN_AIR_LIFT)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_Hurt)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_ShellIdle)
            EndIf
            ExecWait(EVS_Enemy_AirLift)
        CaseEq(EVENT_BLOW_AWAY)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_Hurt)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_ShellIdle)
            EndIf
            ExecWait(EVS_Enemy_BlowAway)
            Return
        CaseEq(EVENT_AIR_LIFT_FAILED)
            Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_Idle)
                ExecWait(EVS_Enemy_NoDamageHit)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_Terratroopa_ShellIdle)
                ExecWait(EVS_Enemy_NoDamageHit)
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_RESTART)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, PHASE_FIRST_STRIKE)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellSpin)
    Else
        Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
        IfEq(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, AVAR_HiddenTurns, LVar0)
            Sub(LVar0, 1)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, AVAR_HiddenTurns, LVar0)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekStart)
                Wait(52)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekEnd)
                Wait(6)
            Else
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekStart)
                Wait(52)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekEnd)
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellOut)
                Wait(17)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Idle)
                Call(SetActorVar, ACTOR_SELF, AVAR_IsHidden, false)
                Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(DefaultAnims))
                Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(NormalDefense))
                Call(SetTargetOffset, ACTOR_SELF, PRT_MAIN, 0, 15)
                Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLIPPED, false)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, true)
            Return
        EndIf
        Call(UseBattleCamPreset, BTL_CAM_ENEMY_APPROACH)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellIn)
        Wait(17)
        ChildThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 4)
            PlayEffect(EFFECT_SMOKE_IMPACT, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0)
            Wait(3)
            PlayEffect(EFFECT_SMOKE_IMPACT, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0)
            Wait(2)
            PlayEffect(EFFECT_SMOKE_IMPACT, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0)
        EndChildThread
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SHELL_SPIN)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellSpin)
        Wait(10)
        Call(SetBattleCamTargetingModes, BTL_CAM_YADJ_TARGET, BTL_CAM_XADJ_AVG, false)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SHELL_TOSS)
    Call(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_WALK, SOUND_NONE, SOUND_NONE)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, false)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, PHASE_FIRST_STRIKE)
                Call(UseBattleCamPreset, BTL_CAM_ACTOR_TARGET_MIDPOINT)
                Call(SetBattleCamDist, 300)
                Call(SetBattleCamOffsetY, 20)
                Call(MoveBattleCamOver, 10)
                Call(SetBattleCamTargetingModes, BTL_CAM_YADJ_TARGET, BTL_CAM_XADJ_AVG, false)
            EndIf
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellOut)
            Wait(17)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            IfEq(LVarA, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Hurt)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, PRT_MAIN, 0, ACTOR_DECORATION_SWEAT)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Hurt)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, false)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Idle)
            Call(RemoveActorDecoration, ACTOR_SELF, PRT_MAIN, 0)
            Call(SetPartYaw, ACTOR_SELF, PRT_MAIN, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, true)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, false)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, SUPPRESS_EVENT_ALL, 0, dmgShellToss, BS_FLAGS1_TRIGGER_EVENTS)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
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
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellOut)
            Wait(17)
            Call(YieldTurn)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Terratroopa_Run)
            ExecWait(EVS_Enemy_ReturnHome)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Idle)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

// EvtScript EVS_TakeTurn = {
//     Call(UseIdleAnimation, ACTOR_SELF, false)
//     Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
//     Call(GetBattlePhase, LVar0)
//     IfEq(LVar0, PHASE_FIRST_STRIKE)
//         Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellSpin)
//     Else
//         ExecWait(EVS_Move_Hide)
//         Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
//         IfEq(LVar0, true)
//             Return
//         EndIf
//     EndIf
//     ExecWait(EVS_Attack_ShellToss)
//     Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
//     Call(UseIdleAnimation, ACTOR_SELF, true)
//     Return
//     End
// };

// EvtScript EVS_Move_Hide = {
//     Call(UseIdleAnimation, ACTOR_SELF, false)
//     Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
//     Call(GetActorVar, ACTOR_SELF, AVAR_IsHidden, LVar0)
//     IfEq(LVar0, 1)
//         Call(GetActorVar, ACTOR_SELF, AVAR_HiddenTurns, LVar0)
//         Sub(LVar0, 1)
//         IfGt(LVar0, 0)
//             Call(SetActorVar, ACTOR_SELF, AVAR_HiddenTurns, LVar0)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekStart)
//             Wait(52)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekEnd)
//             Wait(6)
//         Else
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekStart)
//             Wait(52)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_PeekEnd)
//             Wait(6)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellOut)
//             Wait(17)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Idle)
//             Call(SetActorVar, ACTOR_SELF, AVAR_IsHidden, false)
//             Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(DefaultAnims))
//             Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(NormalDefense))
//             Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLIPPED, false)
//         EndIf
//         Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
//         Call(UseIdleAnimation, ACTOR_SELF, true)
//         Return
//     EndIf
//     Return
//     End
// };

// EvtScript EVS_Attack_ShellToss = {
//     Call(UseIdleAnimation, ACTOR_SELF, false)
//     Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
//     Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
//     Call(UseBattleCamPreset, BTL_CAM_ENEMY_APPROACH)
//     Call(BattleCamTargetActor, ACTOR_SELF)
//     Wait(10)
//     Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellIn)
//     Wait(17)
//     ChildThread
//         Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//         Add(LVar1, 4)
//         PlayEffect(EFFECT_SMOKE_IMPACT, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0)
//         Wait(3)
//         PlayEffect(EFFECT_SMOKE_IMPACT, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0)
//         Wait(2)
//         PlayEffect(EFFECT_SMOKE_IMPACT, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0)
//     EndChildThread
//     Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SHELL_SPIN)
//     Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellSpin)
//     Wait(10)
//     Call(SetBattleCamTargetingModes, BTL_CAM_YADJ_TARGET, BTL_CAM_XADJ_AVG, false)
//     Call(PlaySoundAtActor, ACTOR_SELF, SOUND_SHELL_TOSS)
//     Call(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_WALK, SOUND_NONE, SOUND_NONE)
//     Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
//     Switch(LVar0)
//         CaseOrEq(HIT_RESULT_MISS)
//         CaseOrEq(HIT_RESULT_LUCKY)
//             Set(LVarA, LVar0)
//             Call(SetGoalToTarget, ACTOR_SELF)
//             Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
//             Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
//             Call(RunToGoal, ACTOR_SELF, 0, false)
//             Call(GetBattlePhase, LVar0)
//             IfEq(LVar0, PHASE_FIRST_STRIKE)
//                 Call(UseBattleCamPreset, BTL_CAM_ACTOR_TARGET_MIDPOINT)
//                 Call(SetBattleCamDist, 300)
//                 Call(SetBattleCamOffsetY, 20)
//                 Call(MoveBattleCamOver, 10)
//                 Call(SetBattleCamTargetingModes, BTL_CAM_YADJ_TARGET, BTL_CAM_XADJ_AVG, false)
//             EndIf
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellOut)
//             Wait(17)
//             Call(ResetAllActorSounds, ACTOR_SELF)
//             Call(SetActorYaw, ACTOR_SELF, 180)
//             Wait(4)
//             IfEq(LVarA, HIT_RESULT_LUCKY)
//                 Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
//             EndIf
//             Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//             Add(LVar1, 20)
//             Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//             Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
//             Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Hurt)
//             Wait(6)
//             Sub(LVar1, 20)
//             Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//             Call(JumpToGoal, ACTOR_SELF, 5, false, true, false)
//             Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
//             Call(YieldTurn)
//             Call(SetActorYaw, ACTOR_SELF, 180)
//             Call(AddActorDecoration, ACTOR_SELF, PRT_MAIN, 0, ACTOR_DECORATION_SWEAT)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Hurt)
//             Call(SetGoalToHome, ACTOR_SELF)
//             Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
//             Call(RunToGoal, ACTOR_SELF, 0, false)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Idle)
//             Call(RemoveActorDecoration, ACTOR_SELF, PRT_MAIN, 0)
//             Call(SetPartYaw, ACTOR_SELF, PRT_MAIN, 0)
//             Call(SetActorYaw, ACTOR_SELF, 0)
//             Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
//             Call(UseIdleAnimation, ACTOR_SELF, true)
//             Return
//         EndCaseGroup
//     EndSwitch
//     Call(SetGoalToTarget, ACTOR_SELF)
//     Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
//     Call(RunToGoal, ACTOR_SELF, 0, false)
//     Call(ResetAllActorSounds, ACTOR_SELF)
//     Wait(2)
//     Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, SUPPRESS_EVENT_ALL, 0, dmgShellToss, BS_FLAGS1_TRIGGER_EVENTS)
//     Switch(LVar0)
//         CaseOrEq(HIT_RESULT_HIT)
//         CaseOrEq(HIT_RESULT_NO_DAMAGE)
//             Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
//             Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//             Add(LVar0, 40)
//             Set(LVar1, 0)
//             Call(SetActorJumpGravity, ACTOR_SELF, Float(1.8))
//             Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//             Call(JumpToGoal, ACTOR_SELF, 10, false, true, false)
//             Add(LVar0, 30)
//             Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//             Call(JumpToGoal, ACTOR_SELF, 8, false, true, false)
//             Add(LVar0, 20)
//             Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
//             Call(JumpToGoal, ACTOR_SELF, 6, false, true, false)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_ShellOut)
//             Wait(17)
//             Call(YieldTurn)
//             SetConst(LVar0, PRT_MAIN)
//             SetConst(LVar1, ANIM_Terratroopa_Run)
//             ExecWait(EVS_Enemy_ReturnHome)
//             Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Terratroopa_Idle)
//         EndCaseGroup
//     EndSwitch
//     Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
//     Call(UseIdleAnimation, ACTOR_SELF, true)
// };

} // namespace terratroopa
