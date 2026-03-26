#include "input_capture_service.hpp"

#include "tactics_camera.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "util/utility_vec.hpp"

#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event_joypad_button.hpp"
#include "godot_cpp/classes/input_event_joypad_motion.hpp"
#include "godot_cpp/classes/input_event_key.hpp"
#include "godot_cpp/classes/input_event_mouse_button.hpp"
#include "godot_cpp/classes/input_event_mouse_motion.hpp"
#include "godot_cpp/classes/physics_direct_space_state3d.hpp"
#include "godot_cpp/classes/physics_ray_query_parameters3d.hpp"
#include "godot_cpp/classes/viewport.hpp"
#include "godot_cpp/classes/world3d.hpp"

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
        if (input_event_key->is_pressed()) {
            //keys
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
            for (const auto action : CAMERA_PAN_KEYS) {
                if (input_event_key->is_action(action)) {
                    m_input_capture_resource->m_cam_direction = godot::Input::get_singleton()->get_vector("camera_left", "camera_right", "camera_forward", "camera_backwards");
                    return;
                }
            }
        } else {
            //Handle key releases
            for (const auto action : CAMERA_PAN_KEYS) {
                if (input_event_key->is_action_released(action)) {
                    //Recalculate cam_direction after key release
                    m_input_capture_resource->m_cam_direction = godot::Input::get_singleton()->get_vector("camera_left", "camera_right", "camera_forward", "camera_backwards");
                    return;
                }
            }
        }
    } else if (godot::Ref<godot::InputEventJoypadMotion> input_event_joypad_motion{event}; input_event_joypad_motion.is_valid()) {
        // joystick
        // camera pan direction (left joystick)
        if (input_event_joypad_motion->get_axis() == godot::JOY_AXIS_LEFT_X || input_event_joypad_motion->get_axis() == godot::JOY_AXIS_LEFT_Y) {
            m_input_capture_resource->m_left_stick_x = godot::Input::get_singleton()->get_joy_axis(0, godot::JOY_AXIS_LEFT_X);
            m_input_capture_resource->m_left_stick_y = godot::Input::get_singleton()->get_joy_axis(0, godot::JOY_AXIS_LEFT_Y);

            //Calculate the magnitude of the joystick input
            float magnitude = godot::Vector2(m_input_capture_resource->m_left_stick_x, m_input_capture_resource->m_left_stick_y).length();
            if (magnitude > CONTROLLER_DEADZONE) {
                m_input_capture_resource->m_cam_direction = godot::Vector2(m_input_capture_resource->m_left_stick_x, m_input_capture_resource->m_left_stick_y);
            } else {
                m_input_capture_resource->m_cam_direction = {0,0};
            }
        }
        //camera free look direction (right joystick)
        if (input_event_joypad_motion->get_axis() == godot::JOY_AXIS_RIGHT_X || input_event_joypad_motion->get_axis() == godot::JOY_AXIS_RIGHT_Y) {
            if (godot::Math::abs(input_event_joypad_motion->get_axis_value()) > CONTROLLER_DEADZONE) {
                m_input_capture_resource->m_right_stick_x = -godot::Input::get_singleton()->get_joy_axis(0, godot::JOY_AXIS_RIGHT_X);
                m_input_capture_resource->m_right_stick_y = godot::Input::get_singleton()->get_joy_axis(0, godot::JOY_AXIS_RIGHT_Y);
            } else if (godot::Math::abs(input_event_joypad_motion->get_axis_value()) < CONTROLLER_DEADZONE) {
                m_input_capture_resource->m_right_stick_x = 0.0f;
                m_input_capture_resource->m_right_stick_y = 0.0f;
            }
        }
    } else if (godot::Ref<godot::InputEventJoypadButton> input_event_joypad_button{event}; input_event_joypad_button.is_valid()) {
        //todo: finish
    }

}

void tog::InputCaptureService::hanlde_input(const godot::Ref<godot::InputEvent>& event) {
    return;
}

godot::CollisionObject3D* tog::InputCaptureService::project_mouse_position(int collison_mask, bool is_joystick, const tog::InputCapture* input_capture) {
    if (!m_input_capture_resource) {
        return nullptr;
    }

    auto camera_node = input_capture->get_viewport()->get_camera_3d();
    m_input_capture_resource->m_mouse_position = input_capture->get_viewport()->get_mouse_position();
    godot::Vector2 pointer_origin = (!is_joystick) ? m_input_capture_resource->m_mouse_position : input_capture->get_viewport()->get_visible_rect().size / 2;

    godot::Vector3 from = camera_node->project_ray_origin(pointer_origin);
    godot::Vector3 to = from + camera_node->project_ray_origin(pointer_origin) * RAY_LENGTH;

    //todo: debug log
    auto ray_query = godot::PhysicsRayQueryParameters3D::create(from, to, collison_mask, {});
    auto collider = input_capture->get_world_3d()->get_direct_space_state()->intersect_ray(ray_query);
    godot::Object* obj = collider.is_empty() ? nullptr : collider["collider"];

    return rl::gdcast<godot::CollisionObject3D>(obj);
}
