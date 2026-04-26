#include "tactics_player.hpp"

#include "tactics_player_service.hpp"
#include "util/engine.hpp"

void tog::TacticsPlayer::_ready() {
    //call the parent ready function
    TacticsParticipant::_ready();
    //Initialize the player service with necessary resources
    m_tactics_player_service = memnew(TacticsPlayerService(
        m_tactics_participant_resource,
        m_tactics_camera_resource,
        m_tactics_controls_resource,
        m_tactics_arena
    ));
}

void tog::TacticsPlayer::_physics_process(double p_delta) {
    //Toggle the display of enemy stats
    if (not rl::engine::editor_active()) {
        m_tactics_player_service->toggle_enemy_stats(get_node_or_null("../" + godot::String(tog::node::name::BattleTest::TacticsOpponent)));
    }
}

bool tog::TacticsPlayer::is_pawn_configured() {
    return m_tactics_player_service->is_pawn_configured(this);
}

void tog::TacticsPlayer::show_avaliable_pawn_actions() {
    m_tactics_player_service->show_available_pawn_actions();
}

void tog::TacticsPlayer::show_avaliable_movements() {
    m_tactics_player_service->show_available_movements();
}

void tog::TacticsPlayer::display_attackable_targets() {
    m_tactics_player_service->display_attackable_pawns();
}

void tog::TacticsPlayer::move_pawn() {
    m_tactics_player_service->move_pawn();
}
