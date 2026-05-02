#pragma once

#include "tactics_debug.hpp"
#include "input_capture.hpp"
#include "resources/battle/input_capture_resource.hpp"

#include "godot_cpp/classes/collision_object3d.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "godot_cpp/classes/object.hpp"

namespace tog {

    static constexpr float FL_ROT_SPEED_DIVIDER = 0.25f;

    class InputCapture;

    class InputCaptureService : public godot::RefCounted {
        GDCLASS(InputCaptureService, godot::RefCounted);

    public:

        InputCaptureService() = default;
        InputCaptureService(const godot::Ref<tog::InputCaptureResource>& resource) : m_input_capture_resource(resource) {};
        ~InputCaptureService() override = default;

        void process_input(const godot::Ref<godot::InputEvent>& event);

        void handle_input(const godot::Ref<godot::InputEvent>& event);

        godot::CollisionObject3D* project_mouse_position(int collison_mask, bool is_joystick, const tog::InputCapture* input_capture);

        //void setup_debug_ray(godot::Node3D parent);
        //void draw_debug_ray(godot::Vector3 from, godot::Vector3 to, godot::MeshInstance3D debug_ray_mesh, godot::Node3D parent);

    protected:
        void static _bind_methods() {}

    private:
        godot::Ref<tog::InputCaptureResource>   m_input_capture_resource;
        tog::debug::Logger* m_logger { tog::debug::Logger::get() };
    };

}

