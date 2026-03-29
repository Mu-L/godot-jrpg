#include "input_capture.hpp"

void tog::InputCapture::_ready() {
    //todo: load the input capture resource
    //m_input_capture_resource = godot::ResourceLoader::get_singleton()->load(tog::path::resource::battle::input_capture);
    m_input_capture_service = memnew(InputCaptureService(m_input_capture_resource));
}

void tog::InputCapture::_input(const godot::Ref<godot::InputEvent>& p_event) {
    m_input_capture_service->process_input(p_event);
}

void tog::InputCapture::_process(double p_delta) {
    //debug
    //project_mouse_position(1, false);
}

void tog::InputCapture::_unhandled_input(const godot::Ref<godot::InputEvent> &p_event) {
    m_input_capture_service->handle_input(p_event);
}

godot::Object* tog::InputCapture::project_mouse_position(int collison_mask, bool is_joystick) {
    return m_input_capture_service->project_mouse_position(collison_mask, is_joystick, this);
}
