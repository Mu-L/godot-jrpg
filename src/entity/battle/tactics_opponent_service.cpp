#include "tactics_opponent_service.hpp"

#include "tactics_arena.hpp"
#include "tactics_pawn.hpp"
#include "tactics_opponent.hpp"

bool tog::TacticsOpponentService::is_pawn_configured(tog::TacticsOpponent* tactics_opponent) {
    for (const godot::Variant& variant : tactics_opponent->get_children()) {
        auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
        if (!pawn->center())    return false;
    }
    return true;
}

void tog::TacticsOpponentService::choose_pawn(tog::TacticsOpponent* tactics_opponent) {
    m_tactics_arena->reset_all_tile_markers();
    for (const godot::Variant& variant : tactics_opponent->get_children()) {
        auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
        if (pawn->can_act() && pawn->is_alive()) {
            m_tactics_participant_resource->m_tactics_pawn = pawn;
            m_tactics_participant_resource->m_stage = tog::STAGE::SHOW_ACTION;
            return;
        }
    }
}

void tog::TacticsOpponentService::chase_nearest_enemy(tog::TacticsOpponent* tactics_opponent, godot::Node* player_node) {
    if (m_tactics_participant_resource->m_tactics_pawn->m_tactics_pawn_resource->m_can_move) {
        m_tactics_arena->reset_all_tile_markers();
        m_tactics_arena->process_surrounding_tiles(
            m_tactics_participant_resource->m_tactics_pawn->get_tile(),
            m_tactics_participant_resource->m_tactics_pawn->m_stats_node->m_movement,
            tactics_opponent->get_children()
        );
        m_tactics_arena->mark_attackable_tiles(
            m_tactics_participant_resource->m_tactics_pawn->get_tile(),
            m_tactics_participant_resource->m_tactics_pawn->m_stats_node->m_movement
        );
    }
}

void tog::TacticsOpponentService::is_pawn_done_moving() {

}

void tog::TacticsOpponentService::choose_pawn_to_attack() {

}
