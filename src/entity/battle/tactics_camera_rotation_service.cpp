#include "tactics_camera_rotation_service.hpp"

#include "resources/battle/input_capture_resource.hpp"

#include "godot_cpp/classes/property_tweener.hpp"
#include "godot_cpp/variant/callable_method_pointer.hpp"

tog::TacticsCameraRotationService::TacticsCameraRotationService(tog::TacticsCameraResource *camera_resource, tog::TacticsControlResource *control_resource) {
    m_tactics_camera_resource = camera_resource;
    m_tactics_control_resource = control_resource;
}

void tog::TacticsCameraRotationService::free_look(float delta, godot::Node3D* t_pivot, godot::Node3D* p_pivot) {
    m_tactics_control_resource->set_cursor_shape_to_move();
    godot::Vector2 input = get_free_look_input();
    apply_free_look_rotation(input, delta, t_pivot, p_pivot);
    reset_twist_pitch_inputs();
}

void tog::TacticsCameraRotationService::rotate_camera(float delta, godot::Node3D* t_pivot, godot::Node3D* p_pivot) {
    godot::Quaternion curr_quat_t = godot::Quaternion::from_euler(t_pivot->get_rotation());
    godot::Quaternion curr_quat_p = godot::Quaternion::from_euler(p_pivot->get_rotation());

    godot::Vector3 destination_t = godot::Vector3(  godot::Math::deg_to_rad(static_cast<float>(m_tactics_camera_resource->m_x_rotation)),
                                                    godot::Math::deg_to_rad(static_cast<float>(m_tactics_camera_resource->m_y_rotation)),
                                                    0);
    godot::Vector3 destination_p = godot::Vector3(0, 0, static_cast<real_t>(m_tactics_camera_resource->m_z_rotation));

    godot::Quaternion target_quat_t = godot::Quaternion::from_euler(destination_t);
    godot::Quaternion target_quat_p = godot::Quaternion::from_euler(destination_p);

    godot::Quaternion new_quat_t = curr_quat_t.slerp(target_quat_t, (m_tactics_camera_resource->m_rot_speed * DELTA_SMOOTHING * delta));
    godot::Quaternion new_quat_p = curr_quat_p.slerp(target_quat_p, (m_tactics_camera_resource->m_rot_speed * DELTA_SMOOTHING * delta));

    t_pivot->set_rotation(new_quat_t.get_euler());
    p_pivot->set_rotation(new_quat_p.get_euler());

    if (godot::Math::is_equal_approx(t_pivot->get_rotation().y, godot::Math::deg_to_rad(static_cast<float>(m_tactics_camera_resource->m_y_rotation)))) {
        m_tactics_camera_resource->m_is_rotating = false;
    }
}

void tog::TacticsCameraRotationService::check_free_look_activation(float delta, tog::TacticsCamera* tactics_camera) {
    if (m_tactics_control_resource->m_is_joystick) { //controller
        if (is_joystick_input_active()) {
            //todo: add debug log
            m_tactics_camera_resource->m_in_free_look = true;
            m_tactics_camera_resource->m_free_look_timer = 0.0;
        } else if (m_tactics_camera_resource->m_in_free_look) {
            update_free_look_timer(delta, tactics_camera);
        } else {
            //todo: add debug log
        }
    } else { // mouse and keyboard
        //Disable as soon as TacticsControl-detected input is released
        if (!tog::InputCaptureResource::m_free_look_pressed && m_tactics_camera_resource->m_in_free_look) {
            deactivate_free_look(tactics_camera);
        }
    }
}

void tog::TacticsCameraRotationService::deactivate_free_look(tog::TacticsCamera* tactics_camera) {
    m_tactics_camera_resource->m_in_free_look = false;
    m_tactics_control_resource->set_cursor_shape_to_move();
    snap_to_nearest_quadrant(tactics_camera);
}

void tog::TacticsCameraRotationService::update_free_look_timer(float delta, tog::TacticsCamera* tactics_camera) {
    m_tactics_camera_resource->m_free_look_timer += delta;
    if ((m_tactics_camera_resource->m_free_look_timer >= tog::FREE_LOOK_TIMEOUT) && m_tactics_camera_resource->m_in_free_look) {
        deactivate_free_look(tactics_camera);
    }
}

void tog::TacticsCameraRotationService::add_angle_to_horizontal_rotation(int twist) {
    if (twist != 0) {
        m_tactics_camera_resource->m_y_rotation = int(godot::Math::fmod(static_cast<float>(m_tactics_camera_resource->m_y_rotation + twist), 360.0f));
        if (m_tactics_camera_resource->m_y_rotation < 0) {
            m_tactics_camera_resource->m_y_rotation += 360;
        }
    }
}

godot::Vector2 tog::TacticsCameraRotationService::get_free_look_input() {
    return (m_tactics_control_resource->m_is_joystick) ? get_free_look_joystick_input() : get_free_look_mouse_input();
}

godot::Vector2 tog::TacticsCameraRotationService::get_free_look_joystick_input() {
    float right_stick_x = tog::InputCaptureResource::m_right_stick_x;
    float right_stick_y = tog::InputCaptureResource::m_right_stick_y;

    godot::Vector2 input{0,0};

    if (godot::Math::abs(right_stick_x) > tog::CONTROLLER_DEADZONE)
        input.x = -right_stick_x * m_tactics_camera_resource->m_rot_speed * RIGHT_STICK_SENSITIVITY;
    if (godot::Math::abs(right_stick_y) > tog::CONTROLLER_DEADZONE)
        input.y = -right_stick_y * m_tactics_camera_resource->m_rot_speed * RIGHT_STICK_SENSITIVITY;

    return input;
}

godot::Vector2 tog::TacticsCameraRotationService::get_free_look_mouse_input() {
    return {m_tactics_camera_resource->m_twist_input, m_tactics_camera_resource->m_pitch_input};
}

void tog::TacticsCameraRotationService::apply_free_look_rotation(godot::Vector2 input, float delta, godot::Node3D* t_pivot, godot::Node3D* p_pivot) {
    t_pivot->rotate_y(input.x * static_cast<real_t>(m_FREE_LOOK_ROT_FACTOR) * delta);
    p_pivot->rotate_x(input.y * static_cast<real_t>(m_FREE_LOOK_ROT_FACTOR) * delta);

    auto new_rotation = p_pivot->get_rotation();

    new_rotation.x = godot::Math::clamp( p_pivot->get_rotation().x,
                                    godot::Math::deg_to_rad(static_cast<float>(m_MIN_VERT_ROT)),
                                        godot::Math::deg_to_rad(static_cast<float>(m_MAX_VERT_ROT)));

    p_pivot->set_rotation(new_rotation);
}

void tog::TacticsCameraRotationService::reset_twist_pitch_inputs() {
    m_tactics_camera_resource->m_twist_input = 0.0f;
    m_tactics_camera_resource->m_pitch_input = 0.0f;
}

bool tog::TacticsCameraRotationService::is_joystick_input_active() {
    float right_stick_x = tog::InputCaptureResource::m_right_stick_x;
    float right_stick_y = tog::InputCaptureResource::m_right_stick_y;
    return ((godot::Math::abs(right_stick_x) > CONTROLLER_DEADZONE) || (godot::Math::abs(right_stick_y) > CONTROLLER_DEADZONE));
}

void tog::TacticsCameraRotationService::snap_to_nearest_quadrant(tog::TacticsCamera* tactics_camera) {
    m_tactics_camera_resource->m_is_snapping_to_quad = true;
    godot::Vector3 nearest_quadrant = calculate_nearest_quadrant(tactics_camera);

    godot::Vector3 current_rotation = tactics_camera->m_t_pivot->get_rotation_degrees();
    godot::Vector3 target_rotation = nearest_quadrant;

    float rotation_difference = target_rotation.y - current_rotation.y;
    if (godot::Math::abs(rotation_difference) > 180) {
        (rotation_difference > 0) ? (target_rotation.y -= 360) : (target_rotation.y += 360);
    }

    auto tween = tactics_camera->create_tween();
    tween->tween_property(tactics_camera->m_t_pivot,
        "rotation_degrees",
        target_rotation,
        m_tactics_camera_resource->m_quad_snap_duration)->set_trans(godot::Tween::TRANS_SINE);
    tween->parallel()->tween_property(tactics_camera->m_p_pivot,
        "rotation_degrees:x",
        m_tactics_camera_resource->m_z_rotation,
        m_tactics_camera_resource->m_quad_snap_duration)->set_trans(godot::Tween::TRANS_SINE);
    tween->tween_callback(callable_mp(this, &tog::TacticsCameraRotationService::on_tween_cb).bind(tactics_camera));

    //Update the target rotation values
    m_tactics_camera_resource->m_y_rotation = static_cast<int>(godot::Math::fmod(target_rotation.y, 360));
    if (m_tactics_camera_resource->m_y_rotation < 0)
        m_tactics_camera_resource->m_y_rotation += 360;
}

godot::Vector3 tog::TacticsCameraRotationService::calculate_nearest_quadrant(tog::TacticsCamera* tactics_camera) {
    float current_rotation = tactics_camera->m_t_pivot->get_rotation_degrees().y;
    std::array<int, 4> quadrants = {45, 135, 225, 315};

    //Normalize the current rotation to be between 0 and 360
    current_rotation = godot::Math::fmod(current_rotation, 360);
    if (current_rotation < 0)
        current_rotation += 360;

    int nearest_quadrant = 0;
    int smallest_difference = 360;

    for (const auto quad : quadrants) {
        float difference = godot::Math::abs(current_rotation - static_cast<float>(quad));
        //Consider the smaller angle
        difference = godot::Math::min(difference, 360 - difference);
        if (difference < smallest_difference) {
            smallest_difference = godot::Math::round(difference);
            nearest_quadrant = godot::Math::round(static_cast<float>(quad));
        }
    }

    return {static_cast<real_t>(m_tactics_camera_resource->m_x_rotation), static_cast<real_t>(nearest_quadrant), 0};
}

void tog::TacticsCameraRotationService::on_tween_cb(tog::TacticsCamera* tactics_camera) {
    auto new_rotation = tactics_camera->m_t_pivot->get_rotation_degrees();
    new_rotation.y = godot::Math::fmod(new_rotation.y, 360);
    if (new_rotation.y < 0)
        new_rotation.y += 360;
    tactics_camera->set_rotation(new_rotation);
    m_tactics_camera_resource->m_is_snapping_to_quad = false;
}



