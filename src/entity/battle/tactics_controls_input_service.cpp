#include "tactics_controls_input_service.hpp"

#include "godot_cpp/classes/input_event_joypad_button.hpp"
#include "godot_cpp/classes/input_event_joypad_motion.hpp"
#include "godot_cpp/classes/texture_rect.hpp"
#include "godot_cpp/classes/viewport.hpp"

tog::TacticsControlsInputService::TacticsControlsInputService(godot::Ref<tog::TacticsControlsResource> controls, godot::Node* input_capture) {
    //needs to be copied
    m_tactics_controls_resource = controls;
    m_input_capture = input_capture;
}

void tog::TacticsControlsInputService::update_mouse_mode() {
    godot::Input::get_singleton()->set_mouse_mode(static_cast<godot::Input::MouseMode>(m_tactics_controls_resource->get_is_joystick()));
}

void tog::TacticsControlsInputService::handle_input(const godot::Ref<godot::InputEvent>& event) {
    godot::Ref<godot::InputEventJoypadButton> joypad_button_event = event;
    godot::Ref<godot::InputEventJoypadMotion> joypad_motion_event = event;

    m_tactics_controls_resource->set_is_joystick(joypad_button_event.is_valid() || joypad_motion_event.is_valid());
}

godot::Object* tog::TacticsControlsInputService::get_3d_canvas_mouse_position(int collision_mask, tog::TacticsControls* tactics_controls) {
    if (is_mouse_hovering_ui_elem(tactics_controls)) {
        return nullptr;
    }

    if (m_input_capture) {
        return rl::gdcast<tog::InputCapture>(m_input_capture)->project_mouse_position(collision_mask, m_tactics_controls_resource->m_is_joystick);
    } else {
        //todo: debug log failure
        return nullptr;
    }
}

bool tog::TacticsControlsInputService::is_mouse_hovering_ui_elem(tog::TacticsControls* tactics_controls, const godot::PackedStringArray& elements) {
    godot::Vector2 mouse_position = tactics_controls->get_viewport()->get_mouse_position();
    for (const auto& node : elements) {
        //pass if nodes does not exist and is not visible
        if (const godot::Control* container{rl::gdcast<godot::Control>(tactics_controls->get_node_or_null(node))}; !container || !container->is_visible())
            continue;

        if (node == "%Actions") {
            //get the child nodes and iterate through them
            for (const godot::Variant& variant : tactics_controls->get_node_or_null(node)->get_children()) {
                //cast variant type to godot::Button
                auto action = godot::Object::cast_to<godot::Button>(variant.get_validated_object());
                if (action && action->get_global_rect().has_point(mouse_position)) {
                    return true;
                }
            }
        } else if (node == "%Hints") {
            //get the child nodes and iterate through them
            for (const godot::Variant& variant : tactics_controls->get_node_or_null(node)->get_children()) {
                //cast variant type to godot::TextureRect
                auto hint = godot::Object::cast_to<godot::TextureRect>(variant.get_validated_object());
                if (hint && hint->get_global_rect().has_point(mouse_position)) {
                    return true;
                }
            }
        }
    }
    return false;
}