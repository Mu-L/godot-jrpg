#include "tactics_pawn_combat_service.hpp"

//todo: finish this
bool tog::TacticsPawnCombatService::attack_target_pawn(tog::TacticsPawn* tactics_pawn, tog::TacticsPawn* target_tactics_pawn, float delta) {
    //Make the attacking pawn face the target
    tactics_pawn->m_tactics_pawn_service->m_tactics_pawn_movement_service->look_at_direction(
        tactics_pawn,
        target_tactics_pawn->get_global_position() - tactics_pawn->get_global_position()
    );

    //Check if the pawn can attack and enough time has passed for the attack animation
    if ( tactics_pawn->m_tactics_pawn_resource->m_can_attack &&
        (tactics_pawn->m_tactics_pawn_resource->m_wait_delay > tog::TacticsPawnResource::MIN_TIME_FOR_ATTACK/4.0) ) {
        //Apply damage to the target pawn
        target_tactics_pawn->m_stats_node->apply_to_current_health(-tactics_pawn->m_stats_node->m_attack_power);
        //Set the attacking state to false
        tactics_pawn->m_tactics_pawn_resource->set_attacking(false);
    }

    //If the minimum time for attack hasn't passed, increment the wait delay
    if (tactics_pawn->m_tactics_pawn_resource->m_wait_delay < tog::TacticsPawnResource::MIN_TIME_FOR_ATTACK) {
        tactics_pawn->m_tactics_pawn_resource->m_wait_delay += delta;
        return false;
    }

    //Reset the wait delay and return true to indicate the attack is complete
    tactics_pawn->m_tactics_pawn_resource->m_wait_delay = 0;
    return true;
}
