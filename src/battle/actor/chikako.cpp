#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "sprite/npc/Tatanga.h"

namespace chikako {

extern EvtScript EVS_Init;
extern s32 DefaultAnims[];
extern s32 ChargedAnims[];
extern EvtScript EVS_Idle;
extern EvtScript EVS_TakeTurn;
extern EvtScript EVS_HandleEvent;
extern EvtScript EVS_OnDefeat;
extern EvtScript EVS_Move_Charge;
extern EvtScript EVS_Attack_Slam;
extern EvtScript EVS_KnockDown;
extern EvtScript EVS_Explode;


enum ActorPartIDs {
    PRT_MAIN            = 1,
};

enum ActorVars {
    AVAR_TurnCounter            = 0,
    AVAL_TurnOne                = 1,
    AVAL_TurnTwo                = 2,
};

// Actor Stats
constexpr s32 hp = 1;
constexpr s32 dmgSlam = 6;

s32 DefenseTable[] = {
    ELEMENT_NORMAL,     0,
    ELEMENT_END,
};

s32 StatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,               0,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,               0,
    STATUS_KEY_UNUSED,              0,
    STATUS_KEY_STATIC,              0,
    STATUS_KEY_PARALYZE,            0,
    STATUS_KEY_SHRINK,              0,
    STATUS_KEY_STOP,                0,
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
        .targetOffset = { 0, 33 },
        .opacity = 255,
        .idleAnimations = DefaultAnims,
        .defenseTable = DefenseTable,
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
};

extern "C" export ActorBlueprint blueprint = {
    .flags = ACTOR_FLAG_FLYING,
    .maxHP = hp,
    .type = ACTOR_TYPE_CHIKAKO,
    .level = ACTOR_LEVEL_CHIKAKO,
    .partCount = ARRAY_COUNT(ActorParts),
    .partsData = ActorParts,
    .initScript = &EVS_Init,
    .statusTable = StatusTable,
    .escapeChance = 100,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 DefaultAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_Chikako_ChikakoIdle,
    STATUS_END,
};

s32 ChargedAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_Tatanga_Chikako_ChikakoIdleCharged,
    STATUS_END,
};

EvtScript EVS_Init = {
 Call(BindTakeTurn, ACTOR_SELF, Ref(EVS_TakeTurn))
 Call(BindIdle, ACTOR_SELF, Ref(EVS_Idle))
 Call(BindHandleEvent, ACTOR_SELF, Ref(EVS_HandleEvent))
 Call(SetActorVar, ACTOR_SELF, AVAR_TurnCounter, AVAL_TurnOne)
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
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_Hit)
        EndCaseGroup
        CaseEq(EVENT_BURN_HIT)
            ExecWait(EVS_OnDefeat)
        CaseEq(EVENT_BURN_DEATH)
            ExecWait(EVS_OnDefeat)
        CaseEq(EVENT_SPIN_SMASH_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_SpinSmashHit)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            ExecWait(EVS_OnDefeat)
            Return
        CaseEq(EVENT_SHOCK_HIT)
            Call(PlaySoundAtActor, ACTOR_SELF, 0x00000759)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_ShockHit)
            ExecWait(EVS_OnDefeat)
        CaseEq(EVENT_SHOCK_DEATH)
            Call(PlaySoundAtActor, ACTOR_SELF, 0x00000759)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_ShockHit)
            ExecWait(EVS_OnDefeat)
            Return
        CaseOrEq(EVENT_ZERO_DAMAGE)
        CaseOrEq(EVENT_IMMUNE)
        CaseOrEq(EVENT_AIR_LIFT_FAILED)
        EndCaseGroup
        CaseEq(EVENT_DEATH)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoPainNormal)
            ExecWait(EVS_Enemy_Hit)
            ExecWait(EVS_OnDefeat)
            Return
        CaseEq(EVENT_RECOVER_STATUS)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoIdle)
            ExecWait(EVS_Enemy_Recover)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

EvtScript EVS_OnDefeat = {
    ExecWait(EVS_KnockDown)
    ExecWait(EVS_Explode)
    SetConst(LVar0, PRT_MAIN)
    SetConst(LVar1, ANIM_Tatanga_Chikako_ChikakoDeath)
    Set(LVar2, EXEC_DEATH_NO_SPINNING)
    ExecWait(EVS_Enemy_Death)
    Return
    End
};

#define LBL_DEATH 0

EvtScript EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorVar, ACTOR_SELF, AVAR_TurnCounter, LVar0)
    Switch(LVar0)
        CaseEq(AVAL_TurnOne)
            ExecWait(EVS_Move_Charge)
        CaseEq(AVAL_TurnTwo)
            ExecWait(EVS_Attack_Slam)
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript EVS_Move_Charge = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
    Call(SetBattleCamDist, 320)
    Call(MoveBattleCamOver, 40)
    Wait(20)
    Thread
        Call(ShakeCam, CAM_BATTLE, 0, 40, Float(0.3))
    EndThread
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoCharging)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_CHARGE_UP)
    Wait(40)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_CHARGE_LIGHTNING)
    Call(SetPartEventFlags, ACTOR_SELF, PRT_MAIN, ACTOR_EVENT_FLAG_ATTACK_CHARGED)
    Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(ChargedAnims))
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoIdleCharged)
    Wait(30)
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 30)
    Call(SetActorVar, ACTOR_SELF, AVAR_TurnCounter, AVAL_TurnOne)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript EVS_Attack_Slam = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Call(SetGoalToTarget, ACTOR_SELF)
    // Animation here
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoAttack)
    Wait(10)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 0)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, -20)
            Add(LVar1, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(9.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
            ExecWait(EVS_Explode)
            Call(SetGoalToTarget, ACTOR_SELF)
            IfEq(LVar0, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Goto(LBL_DEATH)
    EndSwitch
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(9.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, EASING_LINEAR)
    ExecWait(EVS_Explode)
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_NO_CONTACT | DAMAGE_TYPE_BLAST, SUPPRESS_EVENT_ALL, 0, dmgSlam, BS_FLAGS1_TRIGGER_EVENTS) // 6 Damage
    Label(LBL_DEATH)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};

EvtScript EVS_KnockDown = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_FALL_QUICK)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, -15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Tatanga_Chikako_ChikakoDeath)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, false, true, false)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

EvtScript EVS_Explode = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 40)
    Add(LVar2, 2)
    PlayEffect(EFFECT_BLAST, 0, LVar0, LVar1, LVar2, Float(3.0), 30, 0)
    Add(LVar2, 2)
    PlayEffect(EFFECT_SMOKE_RING, 0, LVar0, LVar1, LVar2, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_BULLET_BILL_EXPLODE_A)
    Call(StartRumble, BTL_RUMBLE_PLAYER_MAX)
    Thread
        Call(ShakeCam, CAM_BATTLE, 0, 5, Float(1.0))
    EndThread
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Return
    End
};

} // namespace chikako
