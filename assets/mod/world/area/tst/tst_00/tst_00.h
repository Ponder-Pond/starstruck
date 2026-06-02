/// @file tst_00.h
/// @brief Test Area - Test Map

#include "common.h"
#include "world/area_tst/tst_00/generated.h"
#include "message_ids.h"
#include "map.h"

#include "../tst.h"
#include "mapfs/tst_00_shape.h"
#include "mapfs/tst_00_hit.h"

#include "sprite/player.h"
// #include "sprite/npc/Toadsworth.h"
// #include "sprite/npc/BigBubba.h"
// #include "sprite/npc/Toad.h"
// #include "sprite/npc/LuigiSleeping.h"
// #include "sprite/npc/ParadePeach.h"

namespace tst_00 {

// enum {
//     MF_PurchasedBadge   = MapFlag(0),
//     MF_PurchasedItem    = MapFlag(1),
// };

enum {
    // NPC_Toadsworth,
    // NPC_Bubba,
    // NPC_Luigi,
    // NPC_Peach,
};



extern EvtScript EVS_Main;
extern EvtScript EVS_StartTexPanners;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_Scene_BeginGame;

} // namespace tst_00
