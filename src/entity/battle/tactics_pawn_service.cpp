#include "tactics_pawn_service.hpp"

tog::TacticsPawnService::TacticsPawnService() {
    m_tactics_pawn_movement_service = memnew(TacticsPawnMovementService);
    m_tactics_pawn_combat_service = memnew(TacticsPawnCombatService);
    m_tactics_pawn_animation_service = memnew(TacticsPawnAnimationService);
    m_tactics_pawn_hud_service = memnew(TacticsPawnHudService);
}

void tog::TacticsPawnService::setup(tog::TacticsPawn* tactics_pawn) {
    m_tactics_pawn_animation_service->setup(tactics_pawn);
}

void tog::TacticsPawnService::process(tog::TacticsPawn* const tactics_pawn, float delta) {
    tog::TacticsPawnSprite* character_node = tactics_pawn->get_node<tog::TacticsPawnSprite>(tog::node::name::BattleTest::Character);
    if (character_node) {
        character_node->rotate_sprite(tactics_pawn->get_global_basis());
    }
    m_tactics_pawn_movement_service->move_along_path(tactics_pawn, delta);
    m_tactics_pawn_animation_service->start_animator(tactics_pawn);
    m_tactics_pawn_hud_service->tint_when_unable_to_act(tactics_pawn);
    m_tactics_pawn_hud_service->update_character_health(tactics_pawn);
}

bool tog::TacticsPawnService::attack_target_pawn(tog::TacticsPawn* tactics_pawn, tog::TacticsPawn* target_tactics_pawn, float delta) {
    return m_tactics_pawn_combat_service->attack_target_pawn(tactics_pawn, target_tactics_pawn, delta);
}
