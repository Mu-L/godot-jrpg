#include "tactics_pawn_movement_service.hpp"

#include "util/utility_vec.hpp"

void tog::TacticsPawnMovementService::look_at_direction(tog::TacticsPawn* tactics_pawn, godot::Vector3 dir) {
    godot::Vector3 fixed_dir = dir * ( (godot::Math::abs(dir.x) > godot::Math::abs(dir.z)) ? get_right_vector3() : get_back_vector3() );
    float angle = get_forward_vector3().signed_angle_to(fixed_dir.normalized(), get_up_vector3()) + std::numbers::pi;
    godot::Vector3 new_rotation = get_up_vector3() * angle;
    tactics_pawn->set_rotation(new_rotation);
}

void tog::TacticsPawnMovementService::move_along_path(tog::TacticsPawn* tactics_pawn, float delta) {
    if (tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.is_empty() || !tactics_pawn->m_tactics_pawn_resource->m_is_moving) {
        return;
    }
    start_movement(tactics_pawn);
    if (tactics_pawn->m_tactics_pawn_resource->m_move_direction.length() > 0.5f) {
        perform_movement(tactics_pawn, delta);
        godot::Vector3 first_tile = tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.front();
        if (tactics_pawn->get_global_position().distance_to(first_tile) >= 0.15f) {
            return;
        }
    }
    tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.pop_front();
    reset_movement_state(tactics_pawn);
    check_movement_completion(tactics_pawn);
}

void tog::TacticsPawnMovementService::start_movement(tog::TacticsPawn* tactics_pawn) {
    tactics_pawn->m_tactics_pawn_resource->set_moving(true);
    if (tactics_pawn->m_tactics_pawn_resource->m_move_direction == get_zero_vector3()) {
        //todo: check if its an actually vec3 array
        godot::Vector3  tile_position = tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.front();
        tactics_pawn->m_tactics_pawn_resource->m_move_direction = tile_position - tactics_pawn->get_global_position();
    }

}

void tog::TacticsPawnMovementService::perform_movement(tog::TacticsPawn* tactics_pawn, float delta) {
    look_at_direction(tactics_pawn, tactics_pawn->m_tactics_pawn_resource->m_move_direction);
    godot::Vector3 velocity = calculate_velocity(tactics_pawn, delta);
    float current_speed = calculate_speed(tactics_pawn);
    tactics_pawn->set_velocity(velocity * current_speed);
    tactics_pawn->set_up_direction(get_up_vector3());
    tactics_pawn->move_and_slide();
}

godot::Vector3 tog::TacticsPawnMovementService::calculate_velocity(tog::TacticsPawn *tactics_pawn, float delta) {
}

float tog::TacticsPawnMovementService::calculate_speed(tog::TacticsPawn *tactics_pawn) {
}

void tog::TacticsPawnMovementService::reset_movement_state(tog::TacticsPawn *tactics_pawn) {
}

void tog::TacticsPawnMovementService::check_movement_completion(tog::TacticsPawn *tactics_pawn) {
}
