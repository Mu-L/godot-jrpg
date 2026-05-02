#include "tactics_pawn_movement_service.hpp"
#include "tactics_utility.hpp"
#include "util/utility_vec.hpp"

void tog::TacticsPawnMovementService::look_at_direction(tog::TacticsPawn* tactics_pawn, godot::Vector3 dir) {
    godot::Vector3 fixed_dir = dir * ( (godot::Math::abs(dir.x) > godot::Math::abs(dir.z)) ? get_right_vector3() : get_back_vector3() );
    float angle = get_forward_vector3().signed_angle_to(fixed_dir.normalized(), get_up_vector3()) + std::numbers::pi;
    godot::Vector3 new_rotation = get_up_vector3() * angle;
    tactics_pawn->set_rotation(new_rotation);
}

void tog::TacticsPawnMovementService::move_along_path(tog::TacticsPawn* tactics_pawn, float delta) {
    if (tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.is_empty() || !tactics_pawn->m_tactics_pawn_resource->m_can_move) {
        return;
    }

    m_logger->log()->print("OKAY WE ARE READY TO MOVE");

    start_movement(tactics_pawn);
    if (tactics_pawn->m_tactics_pawn_resource->m_move_direction.length() > 0.5f) {
        perform_movement(tactics_pawn, delta);
        //todo: check if its an actually vec3 array
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

godot::Vector3 tog::TacticsPawnMovementService::calculate_velocity(tog::TacticsPawn* tactics_pawn, float delta) {
    godot::Vector3 pawn_velocity = tactics_pawn->m_tactics_pawn_resource->m_move_direction.normalized();
    if ( tactics_pawn->m_tactics_pawn_resource->m_move_direction.y < -tog::TacticsPawnResource::MIN_HEIGHT_TO_JUMP ) {
        godot::Vector3 first_tile_in_the_stack = tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.front();
        if ( distance_without_y(first_tile_in_the_stack, tactics_pawn->get_global_position()) <= 0.2f ) {
            tactics_pawn->m_tactics_pawn_resource->m_gravity += get_down_vector3() * delta * tog::TacticsPawnResource::GRAVITY_STRENGTH;
            pawn_velocity = (godot::Vector3(tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.front()) - tactics_pawn->get_global_position()).normalized() + tactics_pawn->m_tactics_pawn_resource->m_gravity;
        } else {
            pawn_velocity = remove_y(tactics_pawn->m_tactics_pawn_resource->m_move_direction).normalized();
        }
    }
    return pawn_velocity;
}

float tog::TacticsPawnMovementService::calculate_speed(tog::TacticsPawn* tactics_pawn) {
    float current_speed = tactics_pawn->m_tactics_pawn_resource->m_walk_speed;
    if ( tactics_pawn->m_tactics_pawn_resource->m_move_direction.y > tog::TacticsPawnResource::MIN_HEIGHT_TO_JUMP ) {

        current_speed = godot::Math::clamp(godot::Math::abs(tactics_pawn->m_tactics_pawn_resource->m_move_direction.y) * 2.3f, 3.0f, std::numeric_limits<float>::infinity());
        tactics_pawn->m_tactics_pawn_resource->m_is_jumping = true;
    }
    return current_speed;
}

void tog::TacticsPawnMovementService::reset_movement_state(tog::TacticsPawn* tactics_pawn) {
    tactics_pawn->m_tactics_pawn_resource->m_move_direction = get_zero_vector3();
    tactics_pawn->m_tactics_pawn_resource->m_is_jumping = false;
    tactics_pawn->m_tactics_pawn_resource->m_gravity = get_zero_vector3();
    tactics_pawn->m_tactics_pawn_resource->m_can_move = (tactics_pawn->m_tactics_pawn_resource->m_pathfinding_tile_stack.size() > 0);

}

void tog::TacticsPawnMovementService::check_movement_completion(tog::TacticsPawn* tactics_pawn) {
    if (!tactics_pawn->m_tactics_pawn_resource->m_can_move) {
        tactics_pawn->m_tactics_pawn_resource->set_moving(false);
        tactics_pawn->m_tactics_pawn_sprite->adjust_to_center(tactics_pawn);
    }
}
