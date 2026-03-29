#include "tactics_controls_input_service.hpp"

#include "godot_cpp/classes/input_event_joypad_button.hpp"
#include "godot_cpp/classes/input_event_joypad_motion.hpp"

tog::TacticsControlsInputService::TacticsControlsInputService(godot::Ref<tog::TacticsControlResource> controls, godot::Node* input_capture) {
    m_tactics_controls_resource = controls;
    m_input_capture = input_capture;
}

void tog::TacticsControlsInputService::update_mouse_mode() {
    godot::Input::get_singleton()->set_mouse_mode(static_cast<godot::Input::MouseMode>(m_tactics_controls_resource->get_is_joystick()));
}

void tog::TacticsControlsInputService::handle_input(const godot::Ref<godot::InputEvent> &event) {
    godot::Ref<godot::InputEventJoypadButton> joypad_button_event = event;
    godot::Ref<godot::InputEventJoypadMotion> joypad_motion_event = event;

    m_tactics_controls_resource->set_is_joystick(joypad_button_event.is_valid() || joypad_motion_event.is_valid());
}

godot::Object* tog::TacticsControlsInputService::get_3d_canvas_mouse_position(int collision_mask, tog::TacticsControl* tactics_control) {
    if (is_mouse_hovering_ui_elem(tactics_control)) {
        return nullptr;
    }

    if (m_input_capture) {
        return nullptr;
        //return tactics_control
    } else {
        //todo: debug log failure
        return nullptr;
    }
}
