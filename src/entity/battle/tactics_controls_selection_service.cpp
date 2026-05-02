#include "tactics_controls_selection_service.hpp"

tog::TacticsControlsSelectionService::TacticsControlsSelectionService(
    const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
    const godot::Ref<tog::TacticsArenaResource>& arena_resource,
    const godot::Ref<tog::TacticsControlsResource>& controls_resource,
    const godot::Ref<tog::TacticsCameraResource>& camera_resource,
    const godot::Ref<tog::TacticsControlsInputService>& controls_input_service) {
    m_tactics_participant_resource = participant_resource;
    m_tactics_arena_resource = arena_resource;
    m_tactics_controls_resource = controls_resource;
    m_tactics_camera_resource = camera_resource;
    m_tactics_controls_input_service = controls_input_service;
}

void tog::TacticsControlsSelectionService::select_pawn(tog::TacticsPlayer* const tactics_player, tog::TacticsControls* const tactics_controls) {
    m_logger->log()->print("tog::TacticsControlsSelectionService::select_pawn(tog::TacticsPlayer* const tactics_player, tog::TacticsControls* const tactics_controls)");
    m_tactics_arena_resource->reset_all_tile_markers();
    if ( tactics_controls->m_tactics_pawn ) {
        m_tactics_controls_resource->set_actions_menu_visibility(false, m_tactics_participant_resource->m_tactics_pawn);
        tactics_controls->m_tactics_pawn->show_pawn_stats(false);
        m_logger->log()->print("No Pawn Initally");
    }

    tactics_controls->m_tactics_pawn = godot::Object::cast_to<tog::TacticsPawn>(select_hovered_pawn(tactics_controls));
    if ( tactics_controls->m_tactics_pawn ) {
        tactics_controls->m_tactics_pawn->show_pawn_stats(true);
        m_logger->log()->print("Found Pawn");
    } else {
        m_logger->log()->print("Pawn still not found, returning");
        //return if pawn does not exist
        return;
    }

    //grab input manager
    godot::Input* input_manager = godot::Input::get_singleton();
    if ( input_manager->is_action_just_pressed("ui_accept") && tactics_controls->m_tactics_pawn->can_act() ) {
        //checks to see if the
        if ( tactics_controls->m_tactics_pawn->get_parent() == tactics_player ) {
            //i think you can cast up
            m_tactics_camera_resource->m_target = tactics_controls->m_tactics_pawn;
            m_tactics_controls_resource->set_actions_menu_visibility(true, m_tactics_participant_resource->m_tactics_pawn);
            m_tactics_participant_resource->m_stage = 1;
        }
    }
}

godot::PhysicsBody3D* tog::TacticsControlsSelectionService::select_hovered_pawn(tog::TacticsControls* tactics_controls) {
    auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(m_tactics_controls_input_service->get_3d_canvas_mouse_position(2, tactics_controls));
    auto tile = (pawn) ? (pawn->get_tile()) : (godot::Object::cast_to<tog::TacticsTile>(m_tactics_controls_input_service->get_3d_canvas_mouse_position(1, tactics_controls)));

    m_tactics_arena_resource->mark_hover_tile(tile);

    return pawn ? pawn : ( tile ? godot::Object::cast_to<godot::PhysicsBody3D>(tile->get_tile_occupier()) : nullptr );
}

tog::TacticsTile* tog::TacticsControlsSelectionService::select_hovered_tile(tog::TacticsControls* tactics_controls) {
    tog::TacticsPawn* pawn = godot::Object::cast_to<tog::TacticsPawn>(m_tactics_controls_input_service->get_3d_canvas_mouse_position(2, tactics_controls));
    tog::TacticsTile* tile = (pawn) ? (pawn->get_tile()) : (rl::gdcast<tog::TacticsTile>(m_tactics_controls_input_service->get_3d_canvas_mouse_position(1, tactics_controls)));
    m_tactics_arena_resource->mark_hover_tile(tile);
    return tile;
}

void tog::TacticsControlsSelectionService::select_new_location(tog::TacticsControls* tactics_controls) {
    auto* tile = godot::Object::cast_to<tog::TacticsTile>(m_tactics_controls_input_service->get_3d_canvas_mouse_position(1, tactics_controls));
    m_tactics_arena_resource->mark_hover_tile(tile);
    godot::Input* input_manager = godot::Input::get_singleton();
    if (input_manager->is_action_just_pressed("ui_accept") && tile && tile->m_reachable) {
        tactics_controls->m_tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack = m_tactics_arena_resource->get_pathfinding_tilestack(tile);
        m_tactics_camera_resource->m_target = tile;
        m_tactics_participant_resource->m_stage = 4;
    }
}

void tog::TacticsControlsSelectionService::select_pawn_to_attack(tog::TacticsControls* tactics_controls) {
    m_tactics_controls_resource->set_actions_menu_visibility(true, m_tactics_participant_resource->m_tactics_pawn);

    if (m_tactics_participant_resource->m_attackable_pawn) {
        m_tactics_controls_resource->set_actions_menu_visibility(false, m_tactics_participant_resource->m_attackable_pawn);
        m_tactics_participant_resource->m_attackable_pawn->show_pawn_stats(false);
    }

    tog::TacticsTile* tile = select_hovered_tile(tactics_controls);
    m_tactics_participant_resource->m_attackable_pawn = (tile) ? godot::Object::cast_to<tog::TacticsPawn>(tile->get_tile_occupier()) : nullptr;
    if ( m_tactics_participant_resource->m_attackable_pawn ) {
        tactics_controls->set_actions_menu_visibility(true, m_tactics_participant_resource->m_attackable_pawn);
        m_tactics_participant_resource->m_attackable_pawn->show_pawn_stats(true);
    }

    godot::Input* input_manager = godot::Input::get_singleton();
    if (input_manager->is_action_just_pressed("ui_accept") && tile && tile->m_attackable) {
        m_tactics_camera_resource->m_target = m_tactics_participant_resource->m_attackable_pawn;
        m_tactics_participant_resource->m_stage = 7;
    }

}

void tog::TacticsControlsSelectionService::player_wants_to_move() {
    if (m_tactics_participant_resource->m_display_opponent_stats) {
        m_tactics_participant_resource->m_display_opponent_stats = false;
    }
    m_tactics_participant_resource->m_stage = 2;
}

void tog::TacticsControlsSelectionService::player_wants_to_cancel() {
    if (m_tactics_participant_resource->m_display_opponent_stats) {
        m_tactics_participant_resource->m_display_opponent_stats = false;
    }
    m_tactics_participant_resource->m_stage = (m_tactics_participant_resource->m_stage >  1) ? 1 : 0;
}

void tog::TacticsControlsSelectionService::player_wants_to_wait() {
    if (m_tactics_participant_resource->m_display_opponent_stats) {
        m_tactics_participant_resource->m_display_opponent_stats = false;
    }
    m_tactics_participant_resource->m_tactics_pawn->end_pawn_turn();
    m_tactics_participant_resource->m_stage = 0;
}

void tog::TacticsControlsSelectionService::player_wants_to_skip_turn() {
    if (m_tactics_participant_resource->m_display_opponent_stats) {
        m_tactics_participant_resource->m_display_opponent_stats = false;
    }
    m_tactics_participant_resource->skip_turn();
}

void tog::TacticsControlsSelectionService::player_wants_to_attack() {
    m_tactics_participant_resource->m_stage = 5;
}
