#include "tactics_participant_turn_service.hpp"
#include "tactics_player.hpp"

void tog::TacticsParticipantTurnService::handle_player_turn(float delta, tog::TacticsPlayer* tactics_player, tog::TacticsParticipant* tactics_participant) {
    if (m_tactics_participant_resource->m_turn_just_started) {
        godot::Variant front_node = tactics_player->get_children().front();
        m_tactics_camera_resource->m_target = godot::Object::cast_to<godot::Node3D>(front_node);
        m_tactics_participant_resource->m_turn_just_started = false;
    }
    m_tactics_controls_resource->move_camera(delta);
    m_tactics_controls_resource->set_actions_menu_visibility((m_tactics_participant_resource->m_stage < tog::STAGE::MAX_STAGES), m_tactics_participant_resource->m_tactics_pawn);

    //todo: finish this
    /*
    switch (m_tactics_participant_resource->m_stage) {
        case tog::STAGE::SELECT_PAWN:
            m_tactics_controls_resource->select_pawn(tactics_player);
        case tog::STAGE::SHOW_ACTION:
            //tactics_player->
        default: ;
    }
    */
}

void tog::TacticsParticipantTurnService::handle_opponent_turn(float delta, tog::TacticsOpponent *tactics_opponent,
    tog::TacticsParticipant *tactics_participant) {
}

void tog::TacticsParticipantTurnService::can_act(godot::Node3D *parent) {
}

void tog::TacticsParticipantTurnService::reset_turn(godot::Node3D *parent) {
}

void tog::TacticsParticipantTurnService::skip_turn(tog::TacticsPlayer *player) {
}
