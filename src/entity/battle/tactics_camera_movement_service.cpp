#include "tactics_camera_movement_service.hpp"
#include "util/utility_vec.hpp"

tog::TacticsCameraMovementService::TacticsCameraMovementService(TacticsCameraResource* camera_resource, TacticsControlsResource* control_resource) {
    m_tactics_camera_resource = camera_resource;
    m_tactics_control_resource = control_resource;
}

void tog::TacticsCameraMovementService::move_camera(float h, float v, bool joystick, float delta, TacticsCamera* camera) {
    if (m_tactics_camera_resource->m_target || (h == 0 && v == 0)) {
        return;
    }

    const float angle = godot::Math::atan2(-h,v) + camera->m_t_pivot->get_rotation().y;
    godot::Vector3 dir = get_forward_vector3().rotated(get_up_vector3(), angle);

    //Apply edge_pan_speed if not using joystick
    const float speed_multiplier =  joystick ?  m_tactics_camera_resource->m_joy_pan_speed : m_tactics_camera_resource->m_mouse_pan_speed;
    m_tactics_camera_resource->m_target_velocity = dir * m_tactics_camera_resource->m_move_speed * speed_multiplier;

    //apply joystick magnitude
    if (joystick)
        m_tactics_camera_resource->m_target_velocity *= godot::Math::sqrt(h*h+v*v);

    camera->set_velocity(camera->get_velocity().lerp(   m_tactics_camera_resource->m_target_velocity * VELOCITY_SMOOTHING,
                                                    m_tactics_camera_resource->m_smoothing * DELTA_SMOOTHING * delta));

    if (camera->get_velocity().length() > MIN_THRESHOLD) {
        godot::Vector3 new_position = camera->get_global_position() + camera->get_velocity() * delta;
        godot::Vector3 distance_from_center = new_position - m_tactics_camera_resource->m_boundry_center;

        //clamp position to the boundry if exceeding
        if (distance_from_center.length() > m_tactics_camera_resource->m_boundary_radius) {
            godot::Vector3 clamped_position = m_tactics_camera_resource->m_boundry_center + distance_from_center.normalized() * m_tactics_camera_resource->m_boundary_radius;
            camera->set_global_position(clamped_position);
            camera->set_velocity(get_zero_vector3());
        } else {
            camera->move_and_slide();
        }

    }
}

void tog::TacticsCameraMovementService::focus_on_target(tog::TacticsCamera* camera) {
    if (m_tactics_camera_resource->m_target == nullptr) {
        return;
    }

    godot::Vector3 from = camera->get_global_position();
    godot::Vector3 to = m_tactics_camera_resource->m_target->get_global_position();

    if (from.distance_to(to) <= MIN_DISTANCE) {
        m_tactics_camera_resource->m_target = nullptr;
        return;
    }

    godot::Vector3 velocity = (to - from) * static_cast<real_t>(m_tactics_camera_resource->m_move_speed) / SPEED_DIVIDER;

    //Clamp the target position within the boundary
    godot::Vector3 distance_from_center = to - m_tactics_camera_resource->m_boundry_center;
    if (distance_from_center.length() > m_tactics_camera_resource->m_boundary_radius) {
        to = m_tactics_camera_resource->m_boundry_center + distance_from_center.normalized() * m_tactics_camera_resource->m_boundary_radius;
        velocity = (to - from) * static_cast<real_t>(m_tactics_camera_resource->m_move_speed) / SPEED_DIVIDER;
    }

    camera->set_velocity(velocity);
    camera->set_up_direction(get_up_vector3());
    camera->move_and_slide();
}

void tog::TacticsCameraMovementService::stabilize_camera(float delta, tog::TacticsCamera* camera) {
    if (m_tactics_camera_resource->m_target) {
        return;
    }

    m_tactics_camera_resource->m_target_velocity = get_zero_vector3();
    camera->set_velocity(camera->get_velocity().lerp(get_zero_vector3(), m_tactics_camera_resource->m_smoothing * FAST_SMOOTHING * delta));

    if (camera->get_velocity().length() > MIN_THRESHOLD) {
        camera->move_and_slide();
    }
}


