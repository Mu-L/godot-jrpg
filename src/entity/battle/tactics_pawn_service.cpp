#include "tactics_pawn_service.hpp"

tog::TacticsPawnService::TacticsPawnService() {
    m_tactics_pawn_movement_service = memnew(TacticsPawnMovementService);
    m_tactics_pawn_combat_service = memnew(TacticsPawnCombatService);
    m_tactics_pawn_animation_service = memnew(TacticsPawnAnimationService);
    m_tactics_pawn_hud_service = memnew(TacticsPawnHudService);
}

void tog::TacticsPawnService::setup(tog::TacticsPawn* tactics_pawn) {
}
