#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/SparkSMB2.h"

namespace spark {

extern EvtScript EVS_Init;
extern EvtScript EVS_Idle;
extern EvtScript EVS_TakeTurn;
extern EvtScript EVS_HandleEvent;
extern EvtScript EVS_Move_HomePositionGround;
extern EvtScript EVS_Move_HomePositionAir;
extern EvtScript EVS_Move_HomePositionTop;
extern s32 DefaultAnims[];
extern s32 ChainAnims[];

// Actor Stats
constexpr s32 hp = 6;
constexpr s32 dmgContact = 2;

enum ActorPartIDs {
    PRT_MAIN            = 1,
    PRT_CHAIN           = 2,
};

enum ActorVars {
    AVAR_SwapHomePosition           = 0,
    AVAL_SwapHomePosition_Ground    = 0,
    AVAL_SwapHomePosition_Air       = 1,
    AVAL_SwapHomePosition_Top       = 2,
};

s32 DefenseTable[] = {
    ELEMENT_NORMAL,   1,
    ELEMENT_WATER,    0,
    ELEMENT_BLAST,   -1,
    ELEMENT_SHOCK,   99,
    ELEMENT_END,
};

s32 StatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,               0,
    STATUS_KEY_POISON,            100,
    STATUS_KEY_FROZEN,            100,
    STATUS_KEY_DIZZY,               0,
    STATUS_KEY_UNUSED,            100,
    STATUS_KEY_STATIC,            100,
    STATUS_KEY_PARALYZE,            0,
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
        .targetOffset = { -5, 20 },
        .opacity = 255,
        .idleAnimations = DefaultAnims,
        .defenseTable = DefenseTable,
        .eventFlags = ACTOR_EVENT_FLAG_ELECTRIFIED,
        .elementImmunityFlags = ELEMENT_SHOCK,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = PRT_CHAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = ChainAnims,
        .defenseTable = DefenseTable,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, 0 },
    },
};

extern "C" export ActorBlueprint blueprint = {
    .flags = 0,
    .maxHP = hp,
    .type = ACTOR_TYPE_SPARK,
    .level = ACTOR_LEVEL_SPARK,
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
    STATUS_KEY_NORMAL,    ANIM_SparkSMB2_Idle,
    STATUS_KEY_STONE,     ANIM_SparkSMB2_Still,
    STATUS_KEY_POISON,    ANIM_SparkSMB2_Idle,
    STATUS_KEY_STOP,      ANIM_SparkSMB2_Still,
    STATUS_KEY_STATIC,    ANIM_SparkSMB2_Idle,
    STATUS_KEY_PARALYZE,  ANIM_SparkSMB2_Still,
    STATUS_KEY_FROZEN,    ANIM_SparkSMB2_Still,
    STATUS_END,
};

s32 ChainAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_SparkSMB2_Chain,
    STATUS_END,
};

EvtScript EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(EVS_HandleEvent))
    Call(SetPartEventBits, ACTOR_SELF, PRT_MAIN, ACTOR_EVENT_FLAG_ELECTRIFIED, false)
    Call(GetPartPos, ACTOR_SELF, PRT_CHAIN, LVar0, LVar1, LVar2)
    Sub(LVar1, 10)
    Sub(LVar2, 4)
    Call(SetPartPos, ACTOR_SELF, PRT_CHAIN, LVar0, LVar1, LVar2)
    Return
    End
};

EvtScript EVS_Idle = {
    Return
    End
};

EvtScript EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(EVENT_HIT_COMBO)
        CaseOrEq(EVENT_HIT)
            Call(GetLastElement, LVarE)
            IfFlag(LVarE, DAMAGE_TYPE_WATER)
                Call(SetPartEventBits, ACTOR_SELF, PRT_MAIN, ACTOR_EVENT_FLAG_ELECTRIFIED, false)
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_SparkSMB2_Doused)
                ExecWait(EVS_Enemy_Hit)
            Else
                SetConst(LVar0, PRT_MAIN)
                SetConst(LVar1, ANIM_SparkSMB2_Hurt)
                ExecWait(EVS_Enemy_Hit)
            EndIf
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt) // Burn
            SetConst(LVar2, ANIM_SparkSMB2_Hurt) // BurnStill
            ExecWait(EVS_Enemy_BurnHit)
        CaseEq(EVENT_BURN_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt) // Burn
            SetConst(LVar2, ANIM_SparkSMB2_Hurt) // BurnStill
            ExecWait(EVS_Enemy_BurnHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt) // BurnStill
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt)
            ExecWait(EVS_Enemy_SpinSmashHit)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt) // HurtStill
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_STAR_BEAM)
            // do nothing
        CaseOrEq(EVENT_SHOCK_HIT)
        CaseOrEq(EVENT_SHOCK_DEATH)
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Idle)
            ExecWait(EVS_Enemy_NoDamageHit)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, STATUS_FLAGS_IMMOBILIZED)
                Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_Idle)
                Wait(10)
            EndIf
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt)
            ExecWait(EVS_Enemy_Hit)
            Wait(10)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt) // HurtStill
            ExecWait(EVS_Enemy_Death)
            Return
        CaseEq(EVENT_RECOVER_STATUS)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Idle)
            ExecWait(EVS_Enemy_Recover)
        CaseEq(EVENT_SCARE_AWAY)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_MoveUp)
            SetConst(LVar2, ANIM_SparkSMB2_Hurt)
            ExecWait(EVS_Enemy_ScareAway)
            Return
        CaseEq(EVENT_BEGIN_AIR_LIFT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_MoveDown)
            ExecWait(EVS_Enemy_AirLift)
        CaseEq(EVENT_AIR_LIFT_FAILED)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_MoveDown)
            ExecWait(EVS_Enemy_NoDamageHit)
        CaseEq(EVENT_BLOW_AWAY)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_SparkSMB2_Hurt)
            ExecWait(EVS_Enemy_BlowAway)
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_Idle)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetPartEventFlags, ACTOR_SELF, PRT_MAIN, LVar1)
    IfNotFlag(LVar1, ACTOR_EVENT_FLAG_ELECTRIFIED)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 300)
        // Call(SetBattleCamOffsetY, 55)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 30)
        Wait(30)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_Talk)
        Call(SetPartEventBits, ACTOR_SELF, PRT_MAIN, ACTOR_EVENT_FLAG_ELECTRIFIED, true)
        Wait(30)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_Idle)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 15)
        Wait(15)
    EndIf
    Call(GetActorVar, ACTOR_SELF, AVAR_SwapHomePosition, LVar3)
    Switch(LVar3)
    CaseEq(AVAL_SwapHomePosition_Ground)
        Call(RandInt, 1, LVar4)
        IfEq(LVar4, 0)
            ExecWait(EVS_Move_HomePositionAir)
        Else
            ExecWait(EVS_Move_HomePositionTop)
        EndIf
    CaseEq(AVAL_SwapHomePosition_Air)
        Call(RandInt, 1, LVar4)
        IfEq(LVar4, 0)
            ExecWait(EVS_Move_HomePositionGround)
        Else
            ExecWait(EVS_Move_HomePositionTop)
        EndIf
    CaseEq(AVAL_SwapHomePosition_Top)
        Call(RandInt, 1, LVar4)
        IfEq(LVar4, 0)
            ExecWait(EVS_Move_HomePositionGround)
        Else
            ExecWait(EVS_Move_HomePositionAir)
        EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_Move_HomePositionGround = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 450)
    // Call(SetBattleCamOffsetY, 55)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_MoveDown)
    Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, AVAR_SwapHomePosition, AVAL_SwapHomePosition_Ground)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_Move_HomePositionAir = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_SwapHomePosition, LVar3)
    IfEq(LVar3, AVAL_SwapHomePosition_Ground)
        Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 450)
        // Call(SetBattleCamOffsetY, 55)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 30)
        Wait(30)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 50)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_MoveUp)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(HPBarToHome, ACTOR_SELF)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 15)
        Wait(15)
    Else // AVAL_SwapHomePosition_Top
        Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 450)
        // Call(SetBattleCamOffsetY, 55)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 30)
        Wait(30)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 50)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_MoveDown)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(HPBarToHome, ACTOR_SELF)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 15)
        Wait(15)
    EndIf
    Call(SetActorVar, ACTOR_SELF, AVAR_SwapHomePosition, AVAL_SwapHomePosition_Air)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_Move_HomePositionTop = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_SwapHomePosition, LVar3)
    IfEq(LVar3, AVAL_SwapHomePosition_Ground)
        Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 450)
        // Call(SetBattleCamOffsetY, 55)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 30)
        Wait(30)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 90)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_MoveUp)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(HPBarToHome, ACTOR_SELF)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 15)
        Wait(15)
    Else // AVAL_SwapHomePosition_Air
        Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 450)
        // Call(SetBattleCamOffsetY, 55)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 30)
        Wait(30)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 90)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_SparkSMB2_MoveUp)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(HPBarToHome, ACTOR_SELF)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 15)
        Wait(15)
    EndIf
    Call(SetActorVar, ACTOR_SELF, AVAR_SwapHomePosition, AVAL_SwapHomePosition_Top)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

}; // namespace spark
