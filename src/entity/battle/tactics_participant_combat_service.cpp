#include "tactics_participant_combat_service.hpp"

void tog::TacticsParticipantCombatService::attack_pawn(float delta, bool is_player) {
    //Handle case when no attackable pawn is available
    if ( !m_tactics_participant_resource->m_attackable_pawn ) {
        m_tactics_participant_resource->m_tactics_pawn->m_tactics_pawn_resource->m_can_attack = false;
    } else {
        //Attempt to attack the target pawn
        if ( m_tactics_participant_resource->m_tactics_pawn->attack_target_pawn(m_tactics_participant_resource->m_attackable_pawn, delta) ) {
            return;
        }
        //Hide actions menu and focus camera on attacking pawn
        m_tactics_controls_resource->set_actions_menu_visibility(false, m_tactics_participant_resource->m_attackable_pawn);
        m_tactics_camera_resource->m_target = m_tactics_participant_resource->m_tactics_pawn;
    }

    //Reset attackable pawn
    m_tactics_participant_resource->m_attackable_pawn = nullptr;
    //Reset opponent stats display
    if ( m_tactics_participant_resource->m_display_opponent_stats ) {
        m_tactics_participant_resource->m_display_opponent_stats = false;
    }

    //Determine next stage based on current pawn's ability to act and whether it's a player pawn
    if ( !m_tactics_participant_resource->m_tactics_pawn->can_act() || !is_player ) {
        m_tactics_participant_resource->m_stage = tog::STAGE::SELECT_PAWN;
    } else if ( m_tactics_participant_resource->m_tactics_pawn->can_act() && is_player ) {
        m_tactics_participant_resource->m_stage = tog::STAGE::SHOW_ACTION;
    }

}
