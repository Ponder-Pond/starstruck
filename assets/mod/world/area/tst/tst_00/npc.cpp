#include "tst_00.h"

namespace tst_00 {

// #include "world/common/npc/Bowser.inc.c"

// AnimID ExtraAnims_Bowser[] = {
//     ANIM_WorldBowser_Still,
//     ANIM_WorldBowser_Idle,
//     ANIM_WorldBowser_AngryIdle,
//     ANIM_WorldBowser_Walk,
//     ANIM_WorldBowser_Run,
//     ANIM_WorldBowser_Talk,
//     ANIM_WorldBowser_TalkEyesClosed,
//     ANIM_WorldBowser_AngryTalk,
//     ANIM_WorldBowser_ArmsCrossed,
//     ANIM_WorldBowser_Shock,
//     ANIM_WorldBowser_PostJump,
//     ANIM_WorldBowser_DefeatedIdle,
//     ANIM_WorldBowser_DefeatedTalk,
//     ANIM_LIST_END
// };

// AnimID ExtraAnims_Kammy[] = {
//     ANIM_WorldKammy_Anim01,
//     ANIM_WorldKammy_Anim02,
//     ANIM_WorldKammy_Anim03,
//     ANIM_WorldKammy_Anim04,
//     ANIM_LIST_END
// };

// NpcData NpcData_Bowser = {
//     .id = NPC_Bowser,
//     .settings = &N(NpcSettings_Bowser),
//     .pos = { GEN_BOWSER_VEC },
//     .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
//     .yaw = GEN_BOWSER_DIR,
//     .drops = NO_DROPS,
//     .animations = BOWSER_ANIMS,
//     .extraAnimations = ExtraAnims_Bowser,
// };

// #include "world/common/npc/Kanako.inc.cpp"

// NpcData NpcData_Kanako = {
//     .id = NPC_Kanako,
//     .settings = &NpcSettings_Kanako,
//     .pos = { GEN_KANAKO_VEC },
//     .flags = COMMON_PASSIVE_FLAGS,
//     .yaw = GEN_KANAKO_DIR,
//     .drops = NO_DROPS,
//     .animations = KANAKO_ANIMS,
// };

// NpcGroupList DefaultNPCs = {
//     NPC_GROUP(NpcData_Bowser),
//     NPC_GROUP(NpcData_Kanako),
//     {}
// };

// #include "world/common/npc/Toad_Stationary.inc.c"

// EvtScript EVS_NpcInteract_Toadsworth = {
//     Call(SpeakToPlayer, NPC_Toadsworth, ANIM_Toadsworth_Talk, ANIM_Toadsworth_Idle, 0, MSG_TrainLobby_ToadsworthInteract)
//     Return
//     End
// };

// EvtScript EVS_NpcInit_Toadsworth = {
//     Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Toadsworth))
//     Return
//     End
// };

// EvtScript EVS_NpcInteract_ToadMinister = {
//     Call(SpeakToPlayer, NPC_ToadMinister, ANIM_ToadMinister_Talk, ANIM_ToadMinister_Idle, 0, MSG_TrainLobby_ToadMinisterInteract)
//     Return
//     End
// };

// EvtScript EVS_NpcInit_ToadMinister = {
//     Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_ToadMinister))
//     Return
//     End
// };

// #include "world/common/npc/Bubba.inc.c"

// EvtScript EVS_NpcInteract_Bubba = {
//     Call(SpeakToPlayer, NPC_Bubba, ANIM_BigBubba_Talk, ANIM_BigBubba_Idle, 0, MSG_TrainLobby_BubbaInteract)
//     Return
//     End
// };

// EvtScript EVS_NpcInit_Bubba = {
//     Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Bubba))
//     Return
//     End
// };

// #include "world/common/npc/Luigi.inc.c"

// EvtScript EVS_NpcInteract_Luigi = {
//     Call(DisablePlayerInput, true)
//     Call(ShowMessageAtScreenPos, MSG_TrainLobby_LuigiInteract, 160, 40)
//     // Call(SpeakToPlayer, NPC_Luigi, ANIM_LuigiSleeping_LuigiSleep, ANIM_LuigiSleeping_LuigiSleep, 0, MSG_TrainLobby_LuigiInteract)
//     Call(DisablePlayerInput, false)
//     Return
//     End
// };

// EvtScript EVS_NpcInit_Luigi = {
//     Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Luigi))
//     Return
//     End
// };

// #include "world/common/npc/Peach.inc.c"

// EvtScript EVS_NpcInteract_Peach = {
//     Call(SpeakToPlayer, NPC_Peach, ANIM_ParadePeach_Talk, ANIM_ParadePeach_IdleRaisedArms, 0, MSG_TrainLobby_PeachInteract)
//     Return
//     End
// };

// EvtScript EVS_NpcInit_Peach = {
//     Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Peach))
//     Return
//     End
// };

// NpcData NpcData_Characters[] = {
    // {
    //     .id = NPC_Toadsworth,
    //     .settings = &N(NpcSettings_Toad_Stationary),
    //     .pos = { GEN_TOADSWORTH_VEC },
    //     .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    //     .init = &EVS_NpcInit_Toadsworth,
    //     .yaw = GEN_TOADSWORTH_DIR,
    //     .drops = NO_DROPS,
    //     .animations = TOADSWORTH_ANIMS, // Change to Toadsworth Animations
    //     .tattle = MSG_TrainLobby_ToadsworthTattle,
    // },
    // {
    //     .id = NPC_Bubba,
    //     .settings = &N(NpcSettings_Bubba),
    //     .pos = { GEN_BUBBA_VEC },
    //     .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    //     .init = &EVS_NpcInit_Bubba,
    //     .yaw = GEN_BUBBA_DIR,
    //     .drops = NO_DROPS,
    //     .animations = BUBBA_ANIMS,
    //     .tattle = MSG_TrainLobby_BigBubbaTattle,
    // },
    // {
    //     .id = NPC_Luigi,
    //     .settings = &N(NpcSettings_Luigi),
    //     .pos = { GEN_LUIGI_VEC },
    //     .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    //     .init = &EVS_NpcInit_Luigi,
    //     .yaw = GEN_LUIGI_DIR,
    //     .drops = NO_DROPS,
    //     .animations = LUIGI_SLEEPING_ANIMS,
    //     .tattle = MSG_TrainLobby_LuigiTattle,
    // },
    // {
    //     .id = NPC_Peach,
    //     .settings = &N(NpcSettings_Peach),
    //     .pos = { GEN_PEACH_VEC },
    //     .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    //     .init = &EVS_NpcInit_Peach,
    //     .yaw = GEN_PEACH_DIR,
    //     .drops = NO_DROPS,
    //     .animations = PEACH_NPC_ANIMS,
    //     .tattle = MSG_TrainLobby_PeachTattle,
    // },
// };

// #include "world/common/enemy/Kammy.inc.c"

// EvtScript EVS_NpcInteract_Kammy = {
//     Call(SpeakToPlayer, NPC_CalamityKammy, ANIM_CalamityKammy_Talk, ANIM_CalamityKammy_Idle, 0, MSG_TrainLobby_KammyInteract)
//     Return
//     End
// };

// EvtScript EVS_NpcInit_Kammy = {
//     Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Kammy))
//     Return
//     End
// };

// NpcData NpcData_Kammy = {
//     .id = NPC_Kammy,
//     .settings = &N(NpcSettings_Kammy),
//     .pos = { GEN_CALAMITY_KAMMY_VEC },
//     .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
//     .init = &EVS_NpcInit_Kammy,
//     .yaw = GEN_CALAMITY_KAMMY_DIR,
//     .drops = NO_DROPS,
//     .animations = CALAMITY_KAMMY_ANIMS,
//     .tattle = MSG_TrainLobby_CalamityKammyTattle,
// };

// NpcGroupList DefaultNPCs = {
    // NPC_GROUP(NpcData_Characters),
    // NPC_GROUP(NpcData_Kammy),
    // {}
// };

} // namespace tst_00
