#include "input_capture_service.hpp"
#include "godot_cpp/classes/input_event_mouse_button.hpp"


void tog::InputCaptureService::process_input(const godot::Ref<godot::InputEvent>& event) {

    //recast to an InputEventMouseButton object and check if pressed
    if (godot::Ref<godot::InputEventMouseButton> mouse_button_event{event}; mouse_button_event.is_valid()) {
        //check if any mouse button is pressed at all
        if (mouse_button_event->is_pressed()) {

            if (mouse_button_event->is_action("camera_free_look")) {
                m_input_capture_resource->m_free_look_pressed = true;

            }

        }
    }


}
