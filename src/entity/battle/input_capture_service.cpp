#include "input_capture_service.hpp"

#include "tactics_camera.hpp"
#include "godot_cpp/classes/input_event_key.hpp"
#include "resources/battle/tactics_camera_resource.hpp"

#include "godot_cpp/classes/input_event_mouse_button.hpp"
#include "godot_cpp/classes/input_event_mouse_motion.hpp"


void tog::InputCaptureService::process_input(const godot::Ref<godot::InputEvent>& event) {

    //recast to an InputEventMouseButton object and check if pressed
    if (godot::Ref<godot::InputEventMouseButton> mouse_button_event{event}; mouse_button_event.is_valid()) {
        //check if any mouse button is pressed at all
        if (mouse_button_event->is_pressed()) {
            //if the "free look" option is toggled
            if (mouse_button_event->is_action("camera_free_look")) {
                m_input_capture_resource->m_free_look_pressed = true;
                if (!tog::TacticsCameraResource::m_is_rotating) {
                    tog::TacticsCameraResource::m_in_free_look = true;
                }
            }

            if (const auto button{mouse_button_event->get_button_index()}; button == godot::MouseButton::MOUSE_BUTTON_WHEEL_UP) {
                tog::TacticsCamera::m_tactics_camera_service->m_tactics_zoom_service->zoom_camera(-tog::TacticsCameraResource::m_zoom_speed);
            } else if (button == godot::MouseButton::MOUSE_BUTTON_WHEEL_DOWN) {
                tog::TacticsCamera::m_tactics_camera_service->m_tactics_zoom_service->zoom_camera(tog::TacticsCameraResource::m_zoom_speed);
            }
        } else {
            //free look toggle
            if (mouse_button_event->is_action_released("camera_free_look")) {
                m_input_capture_resource->m_free_look_pressed = false;
            }
        }
    }

    if (godot::Ref<godot::InputEventMouseMotion> mouse_motion_event{event}; mouse_motion_event.is_valid()) {
        //free_look motion capture
        if (tog::TacticsCameraResource::m_in_free_look) {
            tog::TacticsCameraResource::m_twist_input = -mouse_motion_event->get_relative().x * (FL_ROT_SPEED_DIVIDER * tog::TacticsCameraResource::m_rot_speed);
            tog::TacticsCameraResource::m_pitch_input = -mouse_motion_event->get_relative().y * (FL_ROT_SPEED_DIVIDER * tog::TacticsCameraResource::m_rot_speed);
        }
    } else if (godot::Ref<godot::InputEventKey> input_event_key{event}; input_event_key.is_valid()) {
        //keys
        if (input_event_key->is_pressed()) {

            if (input_event_key->is_action_pressed("camera_rotate_left")) {
                if (!tog::TacticsCameraResource::m_in_free_look) {
                    tog::TacticsCameraResource::m_y_rotation += -90;
                }
            } else if (input_event_key->is_action_pressed("camera_rotate_right")) {
                if (!tog::TacticsCameraResource::m_in_free_look) {
                    tog::TacticsCameraResource::m_y_rotation += 90;
                }
            }

            //camera pan direction (WASD)
            if () {

            }
        }

    }

}
