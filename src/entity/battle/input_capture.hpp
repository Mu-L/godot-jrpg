#pragma once

#include "input_capture_service.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "resources/battle/input_capture_resource.hpp"

namespace tog {

    class InputCaptureService;

    class InputCapture : public godot::Node3D {
        GDCLASS(InputCapture, godot::Node3D);

    public:

        InputCapture() = default;
        ~InputCapture() override = default;

        void _ready() override;
        void _input(const godot::Ref<godot::InputEvent>& p_event) override;
        void _process(double p_delta) override;
        void _unhandled_input(const godot::Ref<godot::InputEvent> &p_event) override;
        godot::Object* project_mouse_position(int collison_mask, bool is_joystick);


    protected:
        static void _bind_methods() {}

    private:
        godot::Ref<tog::InputCaptureResource> m_input_capture_resource;
        godot::Ref<tog::InputCaptureService> m_input_capture_service;
    };

}
