#include "tactics_opponent.hpp"

void tog::TacticsOpponent::_ready() {
    TacticsParticipant::_ready();

    m_tactics_opponent_service = memnew(tog::TacticsOpponentService(
        m_tactics_participant_resource,
        m_tactics_camera_resource,
        m_tactics_controls_resource,
        m_tactics_arena)
    );
}

bool tog::TacticsOpponent::is_pawn_configured() {
    m_console->print("tog::TacticsOpponent::is_pawn_configured()");
    return m_tactics_opponent_service->is_pawn_configured(this);
}

void tog::TacticsOpponent::choose_pawn() {
    m_tactics_opponent_service->choose_pawn(this);
}

void tog::TacticsOpponent::chase_nearest_enemy() {
    m_tactics_opponent_service->chase_nearest_enemy(this, get_node_or_null("../TacticsPlayer"));
}

void tog::TacticsOpponent::is_pawn_done_moving() {
    m_tactics_opponent_service->is_pawn_done_moving();
}

void tog::TacticsOpponent::choose_pawn_to_attack() {
    m_tactics_opponent_service->choose_pawn_to_attack();
}
