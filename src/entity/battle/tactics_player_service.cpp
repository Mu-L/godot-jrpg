#include "tactics_player_service.hpp"

void tog::TacticsPlayerService::toggle_enemy_stats(godot::Node* opponent_node) {
    godot::Array enemy_pawns = opponent_node->get_children();

    if (m_tactics_participant_resource->m_display_opponent_stats) {
        for (godot::Variant variant : enemy_pawns) {
            tog::TacticsPawn* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
            pawn->m_tactics_pawn_resource->m_pawn_hud_enabled = true;
            pawn->show_pawn_stats(true);
        }
    } else {
        for (godot::Variant variant : enemy_pawns) {
            tog::TacticsPawn* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
            if (pawn->m_tactics_pawn_resource->m_pawn_hud_enabled == true) {
                pawn->show_pawn_stats(false);
                pawn->m_tactics_pawn_resource->m_pawn_hud_enabled = false;
            }
        }
    }
}

bool tog::TacticsPlayerService::is_pawn_configured(tog::TacticsPlayer* player) {
    for (const godot::Variant& variant : player->get_children()) {
        if (auto* pawn{godot::Object::cast_to<tog::TacticsPawn>(variant)}; (pawn && !pawn->center()) ) {
            //m_console->warn( "PAWN {} IS NOT CONFIGURED", to_std_string(pawn->get_name()) );
            return false;
        }
    }
    return true;
}

void tog::TacticsPlayerService::show_available_pawn_actions() {
    m_tactics_controls_resource->set_actions_menu_visibility(true, m_tactics_participant_resource->m_tactics_pawn);
    m_tactics_arena->reset_all_tile_markers();
    m_tactics_arena->mark_hover_tile(m_tactics_participant_resource->m_tactics_pawn->get_tile());
}

void tog::TacticsPlayerService::show_available_movements() {
    m_tactics_arena->reset_all_tile_markers();

    tog::TacticsPawn* pawn = m_tactics_participant_resource->m_tactics_pawn;
    if (!pawn) return;

    m_tactics_participant_resource->m_display_opponent_stats = true;

    m_tactics_camera_resource->m_target = pawn;
    m_tactics_arena->process_surrounding_tiles(pawn->get_tile(), static_cast<int>(pawn->m_stats_node->m_movement), pawn->get_parent()->get_children());
    m_tactics_arena->mark_reachable_tiles(pawn->get_tile(), pawn->m_stats_node->m_movement);
    m_tactics_participant_resource->m_stage = tog::STAGE::SELECT_LOCATION;
}

void tog::TacticsPlayerService::display_attackable_pawns() {
    m_tactics_arena->reset_all_tile_markers();
    tog::TacticsPawn* pawn = m_tactics_participant_resource->m_tactics_pawn;
    if (!pawn) return;
    m_tactics_participant_resource->m_display_opponent_stats = true;
    m_tactics_arena->process_surrounding_tiles(pawn->get_tile(), static_cast<float>(pawn->m_stats_node->m_attack_range));
    m_tactics_arena->mark_attackable_tiles(pawn->get_tile(), static_cast<float>(pawn->m_stats_node->m_attack_range));
    m_tactics_participant_resource->m_stage = tog::STAGE::SELECT_ATTACK_TARGET;
}

void tog::TacticsPlayerService::move_pawn() {
    tog::TacticsPawn* pawn = m_tactics_participant_resource->m_tactics_pawn;
    m_tactics_controls_resource->set_actions_menu_visibility(false , pawn);
    if ( pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.is_empty() ) {
        m_tactics_participant_resource->m_stage = (!pawn->can_act()) ? tog::STAGE::SELECT_PAWN : tog::STAGE::SHOW_ACTION;
    }
}
