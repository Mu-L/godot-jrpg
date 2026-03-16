#include "input_capture_service.hpp"

#include "../../../extern/godot-engine/core/input/input_enums.h"
#include "resources/battle/tactics_camera_resource.hpp"

#include "godot_cpp/classes/input_event_mouse_button.hpp"


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

            } else if (button == godot::MouseButton::MOUSE_BUTTON_WHEEL_DOWN) {

            }



        }

    }

}