#include "tactics_participant_turn_service.hpp"

#include "tactics_opponent.hpp"
#include "tactics_player.hpp"
#include "tactics_participant_combat_service.hpp"
#include "tactics_participant_service.hpp"

void tog::TacticsParticipantTurnService::handle_player_turn(float delta, tog::TacticsPlayer* tactics_player, tog::TacticsParticipant* tactics_participant) {
    if (m_tactics_participant_resource->m_turn_just_started) {
        godot::Variant front_node = tactics_player->get_children().front();
        m_tactics_camera_resource->m_target = godot::Object::cast_to<godot::Node3D>(front_node);
        m_tactics_participant_resource->m_turn_just_started = false;
    }

    m_tactics_controls_resource->move_camera(delta);
    m_tactics_controls_resource->set_actions_menu_visibility((m_tactics_participant_resource->m_stage < tog::STAGE::MAX_STAGES), m_tactics_participant_resource->m_tactics_pawn);

    switch (m_tactics_participant_resource->m_stage) {
        case tog::STAGE::SELECT_PAWN:
            m_tactics_controls_resource->select_pawn(tactics_player);
        case tog::STAGE::SHOW_ACTION:
            tactics_player->show_avaliable_pawn_actions();
        case tog::STAGE::SHOW_MOVEMENTS:
            tactics_player->show_avaliable_movements();
        case tog::STAGE::SELECT_LOCATION:
            m_tactics_controls_resource->select_new_location();
        case tog::STAGE::MOVE_PAWN:
            tactics_player->move_pawn();
        case tog::STAGE::DISPLAY_TARGETS:
            tactics_player->display_attackable_targets();
        case tog::STAGE::SELECT_ATTACK_TARGET:
            m_tactics_controls_resource->select_pawn_to_attack();
        case tog::STAGE::ATTACK:
            tactics_participant->m_tactics_participant_service->m_tactics_combat_service->attack_pawn(delta, true);
        default: ;
    }
}

void tog::TacticsParticipantTurnService::handle_opponent_turn(float delta, tog::TacticsOpponent* tactics_opponent, tog::TacticsParticipant* tactics_participant) {
    m_tactics_participant_resource->m_targets = tactics_participant->get_node_or_null(tog::node::name::BattleTest::TacticsPlayer);
    m_tactics_controls_resource->set_actions_menu_visibility(false, nullptr);

    if (m_tactics_participant_resource->m_stage > 4) {
        m_tactics_participant_resource->m_stage = tog::STAGE::SELECT_PAWN;
    }

    switch (m_tactics_participant_resource->m_stage) {
        case tog::STAGE::SELECT_PAWN:
            tactics_opponent->choose_pawn();
        case tog::STAGE::SHOW_ACTION:
            tactics_opponent->chase_nearest_enemy();
        case tog::STAGE::SHOW_MOVEMENTS:
            tactics_opponent->is_pawn_done_moving();
        case tog::STAGE::SELECT_LOCATION:
            tactics_opponent->choose_pawn_to_attack();
        case tog::STAGE::MOVE_PAWN:
            tactics_participant->m_tactics_participant_service->m_tactics_combat_service->attack_pawn(delta, false);
        default: ;
    }

}

bool tog::TacticsParticipantTurnService::can_act(godot::Node3D* parent) {
    for (const godot::Variant& variant : parent->get_children()) {
        auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
        if (pawn->can_act()) {
            return true;
        }
    }
    return false;
}

void tog::TacticsParticipantTurnService::reset_turn(godot::Node3D* parent) {
    m_tactics_participant_resource->m_turn_just_started = true;
    for (const godot::Variant& variant : parent->get_children()) {
        auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
        pawn->reset_turn();
    }
}

void tog::TacticsParticipantTurnService::skip_turn(tog::TacticsPlayer* player) {
    for (const godot::Variant& variant : player->get_children()) {
        auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
        pawn->end_pawn_turn();
    }
    m_tactics_participant_resource->m_stage = tog::STAGE::SELECT_PAWN;
}
