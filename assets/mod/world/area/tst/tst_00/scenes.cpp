#include "tst_00.h"

namespace tst_00 {

API_CALLABLE(FadeScreenFromBlack) {
    if (isInitialCall) {
        script->functionTemp[1] = 255;

        // Set overlay color to black
        set_screen_overlay_color(OVERLAY_VIEWPORT_COLOR, 0, 0, 0);
    }

    set_screen_overlay_params_front(OVERLAY_VIEWPORT_COLOR, script->functionTemp[1]);

    if (script->functionTemp[1] == 0) {
        return ApiStatus_DONE2;
    }

    script->functionTemp[1] -= 16;
    if (script->functionTemp[1] <= 0) {
        script->functionTemp[1] = 0;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(SetScreenBlack) {
    set_screen_overlay_color(OVERLAY_VIEWPORT_COLOR, 0, 0, 0);
    set_screen_overlay_params_front(OVERLAY_VIEWPORT_COLOR, 255);
    return ApiStatus_DONE2;
}

EvtScript EVS_Scene_BeginGame = {
    Call(DisablePlayerInput, true)
    // Thread
    //     Wait(5)
    //     Call(SetMusic, 0, SONG_BOWSER_ATTACKS, BGM_VARIATION_1, VOL_LEVEL_FULL)
    //     Wait(5)
    // EndThread
    // Call(SetPlayerAnimation, ANIM_Mario1_TiredIdle)
    // Call(SetNpcAnimation, NPC_Bowser, ANIM_WorldBowser_DefeatedIdle)
    // Wait(60)
    // Call(SpeakToPlayer, NPC_Bowser, ANIM_WorldBowser_DefeatedTalk, ANIM_WorldBowser_DefeatedIdle, 0, MSG_BowsersVilla_DefeatedBowserScene1)
    // Wait(30)
    // Call(SetNpcJumpscale, NPC_Bowser, Float(1.0))
    // Call(GetNpcPos, NPC_Bowser, LVar0, LVar1, LVar2)
    // Sub(LVar0, 50)
    // Call(SetNpcAnimation, NPC_Bowser, ANIM_WorldBowser_Shock)
    // Call(NpcJump0, NPC_Bowser, LVar0, LVar1, LVar2, 20)
    // Call(SetNpcAnimation, NPC_Bowser, ANIM_WorldBowser_PostJump)
    // Call(PlaySoundAtNpc, NPC_Bowser, SOUND_LARGE_NPC_IMPACT, SOUND_SPACE_DEFAULT)
    // Call(ShakeCam, CAM_DEFAULT, 0, 20, Float(2.0))
    // Wait(20)
    // Call(SetNpcAnimation, NPC_Bowser, ANIM_WorldBowser_AngryIdle)
    // Wait(15)
    // Call(SpeakToPlayer, NPC_Bowser, ANIM_WorldBowser_AngryTalk, ANIM_WorldBowser_AngryIdle, 0, MSG_BowsersVilla_DefeatedBowserScene2)
    // Call(SpeakToPlayer, NPC_Bowser, ANIM_WorldBowser_AngryTalk, ANIM_WorldBowser_AngryIdle, 0, MSG_BowsersVilla_DefeatedBowserScene3)
    // Call(SetNpcAnimation, NPC_Bowser, ANIM_WorldBowser_Run)
    // Call(SetPlayerAnimation, ANIM_Mario1_BeforeJump)
    // Call(NpcMoveTo, NPC_Bowser, 25, 0, 8)
    // Wait(5)
    // Thread
    //     Call(PlaySoundAtNpc, NPC_Bowser, SOUND_HIT_NORMAL, SOUND_SPACE_DEFAULT)
    //     Call(SetNpcAnimation, NPC_Bowser, ANIM_WorldBowser_Shock)
    //     Call(ShakeCam, CAM_DEFAULT, 0, 5, Float(1.2))
    // EndThread
    // Wait(5)
    // Call(SetNpcJumpscale, NPC_Bowser, Float(0.1))
    // Call(NpcJump0, NPC_Bowser, 500, 500, 0, 15)
    // Call(ShowMessageAtScreenPos, MSG_BowsersVilla_DefeatedBowserScene4, 160, 40)
    // Thread
    //     Call(SetScreenBlack)
    // EndThread
    // Wait(30)
    Call(DisablePlayerInput, false)
    Return
    End
};

} // namespace tst_00
