#include "tactics_controls_camera_service.hpp"

#include "godot_cpp/classes/input.hpp"

void tog::TacticsControlsCameraService::move_camera(float delta, bool is_joystick) {
    auto input_mgr = godot::Input::get_singleton();
    float h = -input_mgr->get_action_strength("camera_left") + input_mgr->get_action_strength("camera_right");
    float v = input_mgr->get_action_strength("camera_forward") - input_mgr->get_action_strength("camera_backward");
    m_tactics_camera_resource->move_camera(h, v, is_joystick, delta);
}