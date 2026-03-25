#pragma once

#include "input_capture.hpp"
#include "resources/battle/input_capture_resource.hpp"

#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"

namespace tog {

    static constexpr float FL_ROT_SPEED_DIVIDER = 0.25f;

    class InputCaptureService : public godot::Object {
        GDCLASS(InputCaptureService, godot::Object);

    public:

        InputCaptureService() = default;
        InputCaptureService(tog::InputCaptureResource* resource) : m_input_capture_resource(resource) {};
        ~InputCaptureService() override = default;

        void process_input(const godot::Ref<godot::InputEvent>& event);

        void hanlde_input(godot::Ref<godot::InputEvent> event);

        void project_mouse_position(int collison_mask, bool is_joystick, tog::InputCapture input_capture);

        void setup_debug_ray(godot::Node3D parent);

        void draw_debug_ray(godot::Vector3 from, godot::Vector3 to, godot::MeshInstance3D debug_ray_mesh, godot::Node3D parent);

    protected:

        void static _bind_methods() {

        }

    private:
        tog::InputCaptureResource* m_input_capture_resource{nullptr};
    };

}

