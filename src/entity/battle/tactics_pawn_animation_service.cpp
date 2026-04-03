#include "tactics_pawn_animation_service.hpp"

void tog::TacticsPawnAnimationService::setup(const tog::TacticsPawn* tactics_pawn) {
    tactics_pawn->get_node<tog::TacticsPawnSprite>(tog::node::name::BattleTest::Character)->setup(tactics_pawn->m_stats_node, tactics_pawn->m_expertise);
}

void tog::TacticsPawnAnimationService::start_animator(const tog::TacticsPawn* tactics_pawn) {
    tactics_pawn->get_node<tog::TacticsPawnSprite>(tog::node::name::BattleTest::Character)->start_animator(tactics_pawn->m_tactics_pawn_resource->m_move_direction, tactics_pawn->m_tactics_pawn_resource->m_is_jumping);
}
