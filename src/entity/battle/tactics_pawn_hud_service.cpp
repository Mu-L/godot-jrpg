#include "tactics_pawn_hud_service.hpp"

void tog::TacticsPawnHudService::update_character_health(const tog::TacticsPawn* tactics_pawn) {
    godot::Label3D* health_label = tactics_pawn->get_node<godot::Label3D>(tog::node::name::BattleTest::HealthLabel);
    health_label->set_text(godot::String(godot::String::num_int64(tactics_pawn->m_stats_node->m_current_health) + "/" + godot::String::num_int64(tactics_pawn->m_stats_node->m_max_health)));
}

void tog::TacticsPawnHudService::tint_when_unable_to_act(tog::TacticsPawn* tactics_pawn) {
    tog::TacticsPawnSprite* character_node = tactics_pawn->get_node<tog::TacticsPawnSprite>(tog::node::name::BattleTest::Character);
    character_node->set_modulate( tactics_pawn->can_act() ? godot::Color(0.5, 0.5, 0.5) : godot::Color(1, 1, 1) );
}
