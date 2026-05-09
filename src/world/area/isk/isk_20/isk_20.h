/// @file isk_20.h
/// @brief Dry Dry Ruins - Tutankoopa Room

#include "common.h"
#include "world/area_isk/isk_20/generated.h"
#include "message_ids.h"
#include "map.h"

#include "../isk.h"
#include "mapfs/isk_20_shape.h"
#include "mapfs/isk_20_hit.h"

#include "sprite/npc/Goomba.h"
#include "sprite/npc/SpikedGoomba.h"
#include "sprite/npc/KoopaTroopa.h"
#include "sprite/npc/Bobomb.h"
#include "sprite/npc/Cleft.h"
#include "sprite/npc/Bandit.h"
#include "sprite/npc/Pokey.h"
#include "sprite/npc/BuzzyBeetle.h"
#include "sprite/npc/SmallPiranha.h"
#include "sprite/npc/WorldClubba.h"
#include "sprite/npc/ShyGuy.h"
#include "sprite/npc/SpearGuy.h"
#include "sprite/npc/SpikeTop.h"
#include "sprite/npc/BonyBeetle.h"
#include "sprite/npc/HammerBros.h"

namespace isk_20 {

enum NPCIDs {
    NPC_Goomba,
    NPC_SpikedGoomba,
    NPC_KoopaTroopa,
    NPC_Bobomb,
    NPC_Cleft,
    NPC_Bandit,
    NPC_Pokey,
    NPC_BuzzyBeetle,
    NPC_PiranhaPlant,
    NPC_Clubba,
    NPC_ShyGuy,
    NPC_SpearGuy,
    NPC_SpikeTop,
    NPC_BonyBeetle,
    NPC_HammerBros,
};

enum MapVars {
    MV_0    = MapVar(0),
};

enum MapFlags {
    MF_GauntletDefeated    = MapFlag(0),
};

enum BattleNames {
    BTL_TST_FORMATION_0 = 0x2F00,
    BTL_TST_FORMATION_1,
    BTL_TST_FORMATION_2,
    BTL_TST_FORMATION_3,
    BTL_TST_FORMATION_4,
    BTL_TST_FORMATION_5,
    BTL_TST_FORMATION_6,
    BTL_TST_FORMATION_7,
    BTL_TST_FORMATION_8,
    BTL_TST_FORMATION_9,
    BTL_TST_FORMATION_10,
    BTL_TST_FORMATION_11,
    BTL_TST_FORMATION_12,
    BTL_TST_FORMATION_13,
    BTL_TST_FORMATION_14,
};

enum BattleStages {
    BTL_TST_STAGE_0 = 0,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFlames;
extern EvtScript EVS_BindExitTriggers;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_OpenLeftGate;
extern EvtScript EVS_CloseLeftGate;
extern EvtScript EVS_OpenRightGate;
extern EvtScript EVS_CloseRightGate;
extern API_CALLABLE(GetRandomArenaNPC);
extern API_CALLABLE(ResetArenaGauntlet);
extern EvtScript EVS_GauntletRandomizer;

} // namespace isk_20
